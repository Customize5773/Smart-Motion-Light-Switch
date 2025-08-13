#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_NeoPixel.h>

// ======================
// Hardware Configuration
// ======================
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C
#define PIR_PIN 2
#define SSR_PIN 7
#define NEOPIXEL_PIN 6
#define BUTTON_ON 13
#define BUTTON_OFF 10
#define DEBOUNCE_DELAY 50

// =================
// Sensor Thresholds
// =================
const int MOTION_TIMEOUT = 30000;  // 30 seconds
const int DISTANCE_THRESHOLD = 200; // 200 cm
const int BRIGHTNESS_THRESHOLD = 50; // Lux value

// =====================
// Initialize Components
// =====================
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
Adafruit_VL53L0X tofSensor = Adafruit_VL53L0X();
Adafruit_NeoPixel pixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
VL53L0X_RangingMeasurementData_t measure;

// ==================
// Runtime Variables
// ==================
unsigned long lastMotionTime = 0;
bool lightState = false;
bool motionDetected = false;
int ambientLight = 0;

// ==============
// Setup Function
// ==============
void setup() {
  Serial.begin(115200);
  
  // Initialize safety components first
  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);  // Ensure relay is OFF at startup
  
  // Initialize buttons with pullups
  pinMode(BUTTON_ON, INPUT_PULLUP);
  pinMode(BUTTON_OFF, INPUT_PULLUP);
  
  // Sensor initialization
  initSensors();
  
  // Safety check
  if(!tofSensor.begin() || !display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    pixel.begin();
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));  // Red error indicator
    pixel.show();
    while(true);  // Halt on critical failure
  }
  
  // Display boot screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SmartMotionLight v1.0");
  display.println("Safety Status: OK");
  display.display();
  delay(2000);
}

// =============
// Main Loop
// =============
void loop() {
  // 1. Safety-critical operations first
  checkEmergencyStop();
  
  // 2. Sensor data collection
  updateSensorData();
  
  // 3. State control logic
  updateLightState();
  
  // 4. User interface
  updateDisplay();
  handleButtons();
  
  // 5. System heartbeat
  pixel.setPixelColor(0, lightState ? pixel.Color(0, 25, 0) : pixel.Color(0, 0, 5));
  pixel.show();
  delay(100);
}

// ======================
// Sensor Initialization
// ======================
void initSensors() {
  // Configure PIR sensor
  pinMode(PIR_PIN, INPUT);
  
  // Start ToF sensor
  tofSensor.startRangeContinuous();
  
  // Initialize NeoPixel
  pixel.begin();
  pixel.setBrightness(25);
}

// =======================
// Sensor Data Collection
// =======================
void updateSensorData() {
  // Read PIR motion sensor
  motionDetected = digitalRead(PIR_PIN) == HIGH;
  
  // Read distance measurement
  if (tofSensor.isRangeComplete()) {
    tofSensor.readRangeContinuous(&measure);
    if (measure.RangeStatus != 4) {  // Valid data check
      ambientLight = measure.RangeMilliMeter;
    }
  }
}

// =====================
// Light Control Logic
// =====================
void updateLightState() {
  // Manual override check
  if (!lightState && digitalRead(BUTTON_ON) == LOW) {
    lightState = true;
    lastMotionTime = millis();
  }
  
  // Motion-based activation
  if (motionDetected && ambientLight < BRIGHTNESS_THRESHOLD) {
    lightState = true;
    lastMotionTime = millis();
  }
  
  // Timeout deactivation
  if (lightState && (millis() - lastMotionTime > MOTION_TIMEOUT)) {
    lightState = false;
  }
  
  // Safety override - disable in bright conditions
  if (ambientLight >= BRIGHTNESS_THRESHOLD) {
    lightState = false;
  }
  
  // Apply to relay (with safety delay)
  digitalWrite(SSR_PIN, lightState ? HIGH : LOW);
}

// ======================
// User Interface
// ======================
void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0,0);
  
  // System status
  display.print("Light: ");
  display.println(lightState ? "ON " : "OFF");
  
  // Sensor readings
  display.print("Motion: ");
  display.println(motionDetected ? "DETECTED" : "CLEAR");
  display.print("Ambient: ");
  display.print(ambientLight);
  display.println(" lux");
  
  // System info
  display.print("Timeout: ");
  display.print((MOTION_TIMEOUT - (millis() - lastMotionTime)) / 1000);
  display.println("s");
  
  display.display();
}

void handleButtons() {
  static unsigned long lastDebounce = 0;
  
  if ((millis() - lastDebounce) > DEBOUNCE_DELAY) {
    // Manual on button
    if (digitalRead(BUTTON_ON) == LOW) {
      lightState = true;
      lastMotionTime = millis();
      lastDebounce = millis();
    }
    
    // Emergency off button
    if (digitalRead(BUTTON_OFF) == LOW) {
      lightState = false;
      lastDebounce = millis();
    }
  }
}

// =====================
// Safety Critical
// =====================
void checkEmergencyStop() {
  // Immediate shutdown if button pressed
  if (digitalRead(BUTTON_OFF) == LOW) {
    digitalWrite(SSR_PIN, LOW);
    lightState = false;
    
    // Visual alarm
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
    pixel.show();
    delay(500);
    pixel.clear();
    pixel.show();
  }
  
  // Automatic safety cutoff
  if (ambientLight >= BRIGHTNESS_THRESHOLD && lightState) {
    digitalWrite(SSR_PIN, LOW);
    lightState = false;
  }
}
