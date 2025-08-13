# Electrical Safety Guidelines for SmartMotionLight

## Critical Warnings
1. **MAINS VOLTAGE KILLS**  
   - This project involves 120V/230V AC which can cause **fatal electric shock**  
   - Never work on live circuits - disconnect power before modifications  
   - Assume all wires are live until verified with multimeter  

2. **FIRE HAZARD**  
   - Improper relay wiring can cause arcing and electrical fires  
   - SSR must be rated for 125% of your lighting circuit's max current  

## Personal Protection
| Equipment | Specification | Purpose |
|-----------|---------------|---------|
| Insulated Gloves | Class 00 (500V), Leather Over-sleeves | Shock protection |
| Safety Glasses | Polycarbonate, Side Shields | Arc flash protection |
| Multimeter | CAT III 600V minimum | Safe voltage verification |
| Insulated Tools | VDE 1000V certified | Prevents accidental contact |

## Safe Wiring Practices
### AC Mains Wiring
- Use **14AWG minimum** for lighting circuits (12AWG for >15A)  
- Maintain **8mm clearance** between AC and DC circuits  
- Double-insulate all connections with heat shrink tubing  
- Secure wires with strain relief clamps  

### Relay Installation
```plaintext
1. Connect SSR only to the HOT wire (never neutral)  
2. Place 3A fuse on input HOT wire  
3. Use metal-backed thermal pad between SSR and heatsink  
4. Verify NO (Normally Open) terminal configuration  
```

## Fire Prevention
1. **Enclosure Requirements**  
   - Must be UL94 V-0 fire-rated plastic  
   - Minimum 2mm wall thickness  
   - Install flame barrier between AC and DC sections  

2. **Overcurrent Protection**  
   ```mermaid
   graph LR
   A[AC Input] --> B[3A Fuse]
   B --> C[SSR]
   C --> D[Light Fixture]
   ```

3. **Ventilation**  
   - Provide 10mm clearance around SSR  
   - Install ventilation slots at top of enclosure  

## Emergency Procedures
### If Electrical Shock Occurs:
1. **DO NOT** touch victim directly  
2. Disconnect power at breaker  
3. Call emergency services  
4. Administer CPR if certified  

### If Fire Starts:
1. Cut power at main breaker  
2. Use Class C fire extinguisher  
3. Never use water on electrical fires  

## Legal Compliance
- This project is **NOT UL/CE certified**  
- Check local regulations (NEC Article 404 for US, IEC 60669 for EU)  
- Do not install in wet locations (bathrooms, outdoors) without proper IP rating  
