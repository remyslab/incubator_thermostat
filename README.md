# Incubator

This is a simple design to make an incubator. It can be used to incube eggs, fungus, bacteria, yeasts... or make yogurt, tempeh...

There are three main parts :

	- Box (like a cooler, or polystyrene box...)
	- Reptile Heat Cable
	- Precise thermostat

This is how you can built a thermostat with an Arduino (or clone), a relay and a temperature sensors. The total cost is around 5€ with an Arduino clone, but if you can, try to buy true Arduino products to support the team.

## Parts and schematic

**TO DO : List of parts**

**TO DO : Draw a schematic**

## Calibration

Two buffers avoid the box inertia and make your thermostat more precise. For a perfect accuracy, buffers need to be calculated for each target temperature, but the precision is not to bad with a single calibration, around 0 - 0.30 °C for a calibration at 30 °C (that means the temperature stays between 30°C and 30.30°C). 
Two factors can improved the precision : a perfect isolated box (no holes), and a well-fixed temp sensor (the temperature isn't really the same in all of the box, I haven't try to put a little fan for homogenize cool and hot zones but it can be a solution. Personally I'm a bit affraid with the circulation of contaminants). 

**TO DO : tips to calculate buffers**

## Pictures

![alt text](./thermostat.jpg)
