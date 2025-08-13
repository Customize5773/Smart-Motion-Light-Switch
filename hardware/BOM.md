# Bill of Materials - SmartMotionLight

| Category         | Component                   | Specification                           | Qty | Unit Price | Notes |
|------------------|-----------------------------|-----------------------------------------|-----|------------|-------|
| **Core Controller** | Arduino Nano             | ATmega328P, 5V logic                   | 1   | $3.50      | Clone acceptable |
| **Sensors**        | VL53L0X ToF Sensor       | I2C, 0-200cm range                     | 1   | $5.00      | Time-of-Flight precision |
|                  | PIR Motion Sensor        | HC-SR501 (3-7m range)                  | 1   | $1.80      | Adjustable sensitivity |
| **Power Control**  | Solid State Relay (SSR)  | 5V DC Control, 240V AC 25A             | 1   | $6.50      | **Safety Critical** |
| **Display**        | OLED Screen              | 0.96" I2C, 128x64 SSD1306             | 1   | $4.00      | White/blue display |
| **Indicators**     | WS2812B NeoPixel         | 5mm Single LED                         | 1   | $0.30      | Status indicator |
| **Interface**      | Tactile Buttons          | 6x6mm, Through-hole                   | 2   | $0.10      | Momentary push |
| **Power**          | 5V DC Power Supply       | 3A, Barrel Jack                       | 1   | $8.00      | Regulated |
|                  | AC Power Cord            | 18AWG, 1m with plug                   | 1   | $2.50      | Country-specific |
| **Safety**         | Enclosure                | V0 Fire-Rated Plastic, 100x80x50mm     | 1   | $5.00      | UL94 V-0 rating |
|                  | Fuse Holder              | 5x20mm In-line                        | 1   | $1.00      | For AC input |
|                  | Fast-Blow Fuse           | 3A, 250V                              | 1   | $0.50      | AC protection |
| **Connectivity**   | JST Connector Set        | 2-pin (PIR), 4-pin (ToF)              | 2   | $0.40      | For sensors |
|                  | Screw Terminal Block     | 2-pin 5.08mm pitch                    | 2   | $0.30      | For AC wiring |
| **Passives**       | Resistor Kit             | 1/4W, 10Ω-1MΩ                        | 1   | $2.00      | Assorted values |
|                  | Capacitor Kit            | Ceramic 0.1μF-100μF                  | 1   | $3.00      | Decoupling |
| **Hardware**       | PCB Prototype Board      | 5x7cm, 2.54mm pitch                  | 1   | $1.50      | FR4 material |
|                  | M3 Hardware Kit          | Screws, nuts, standoffs               | 1   | $3.00      | For assembly |
| **Cabling**        | Hook-up Wire             | 22AWG Silicone, multi-color           | 1m  | $1.50      | Low-voltage |
|                  | Heat-Shrink Tubing       | 3mm diameter, assorted colors         | 10  | $1.00      | Insulation |
| **Tools**          | Insulated Screwdriver    | VDE 1000V rated                       | 1   | $15.00     | **Safety Critical** |
|                  | Multimeter               | CAT III 600V                         | 1   | $25.00     | Essential for AC work |
|                  | Wire Strippers           | Automatic, 10-24AWG                  | 1   | $12.00     | |

## Estimated Total Cost: $102.90 USD
*(Prices based on typical electronics retailers)*

---

## Critical Safety Components

1. **Solid State Relay (SSR)**  
   - Must be rated for **125% higher** than your circuit's max current  
   - Recommended: Fotek SSR-25DA (25A) with heatsink  

2. **Fire-Retardant Enclosure**  
   - UL94 V-0 certification required  
   - Minimum wall thickness: 2mm  
   - Must fully isolate AC and DC sections  

3. **AC Fusing**  
   - Fast-blow ceramic fuse rated for AC voltage  
   - Positioned on **live wire** before SSR  

4. **Safety Tools**  
   - CAT III multimeter mandatory for AC measurements  
   - Insulated tools required when handling mains voltage  

---

## Recommended Suppliers

| Component Type     | Trusted Suppliers                |
|--------------------|----------------------------------|
| Electronics        | Digi-Key, Mouser, LCSC          |
| Mechanical Parts   | McMaster-Carr, Misumi           |
| Enclosures         | Polycase, Hammond Manufacturing |
| Safety Equipment   | Fluke, Klein Tools              |

---

## Assembly Notes

1. **AC Wiring Rules**  
   - Use **18AWG minimum** for AC connections  
   - Maintain 8mm clearance between AC/DC traces  
   - Double-insulate all mains connections  

2. **Testing Sequence**  
   1. Verify DC circuit without AC connected  
   2. Test relay operation with multimeter (continuity mode)  
   3. First AC test with **incandescent bulb load**  
   4. Final test with intended lighting load  

3. **Certification Warning**  
> This DIY project does not carry UL/CE certification.  
> Not approved for permanent installation in some regions.  
> Consult local electrical codes before deployment.
