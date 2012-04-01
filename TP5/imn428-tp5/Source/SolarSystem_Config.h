#ifndef SOLARSYSTEM_CONFIG_H_
#define SOLARSYSTEM_CONFIG_H_

//	These multipliers have the sole purpose of enhancing the appearance
//	of the scene and scale the different planet characteristics (radius,
//	rotation period, etc.) to make an interesting display of the solar system.
//  When using one of the planet's attributes, you should always multiply
//	the attribute to it's corresponding multiplier. This will allow you 
//  to rescale your solar system without having to modify every constants 
//	independently.

#define MULTIPLIER_EQUAT_RAD	0.5
#define MULTIPLIER_ROTAT_PER	5.0
#define MULTIPLIER_ORBIT_RAD	10.0
#define MULTIPLIER_REVOL_PER	10.0

//EQUATOR_RADIUS	-> Radius of the sphere that makes the planet
//ROTATION_PERIOD	-> Time (in seconds) for a planet to do a full rotation on itself.
//ORBIT_RADIUS		-> Radius of the planet's orbit.
//REVO_PERIOD		-> (Revolution period): Time taken by a planet to do a full revolution around the sun. (Or a moon around it's mother planet.)

#define SUN_EQUATOR_RADIUS		6
#define SUN_ROTATION_PERIOD		25.37 
#define SUN_ORBIT_RADIUS		0

#define MERCURY_EQUATOR_RADIUS	0.38
#define MERCURY_ROTATION_PERIOD	10.0
#define MERCURY_ORBIT_RADIUS	1.2
#define MERCURY_REVO_PERIOD		0.24

#define VENUS_EQUATOR_RADIUS	0.9499
#define VENUS_ROTATION_PERIOD	-5
#define VENUS_ORBIT_RADIUS		1.5
#define VENUS_REVO_PERIOD		0.615

#define EARTH_EQUATOR_RADIUS	1.0
#define EARTH_ROTATION_PERIOD	3.5
#define EARTH_ORBIT_RADIUS		1.9
#define EARTH_REVO_PERIOD		1.0

#define MOON_EQUATOR_RADIUS		0.273
#define MOON_ROTATION_PERIOD	0.00257 * 18
#define MOON_ORBIT_RADIUS		MOON_ROTATION_PERIOD * 2
#define MOON_REVO_PERIOD		0.0739

#define MARS_EQUATOR_RADIUS		0.533
#define MARS_ROTATION_PERIOD	24.622
#define MARS_ORBIT_RADIUS		2.4
#define MARS_REVO_PERIOD		1.8808

#define JUPITER_EQUATOR_RADIUS	11.209	* 0.5
#define JUPITER_ROTATION_PERIOD	9.92425 * 0.5
#define JUPITER_ORBIT_RADIUS	6.20	* 0.6
#define JUPITER_REVO_PERIOD		11.85	* 0.5

#define SATURN_SCALE_FACTOR		0.5
#define SATURN_EQUATOR_RADIUS	9.4492	* 0.5
#define SATURN_ROTATION_PERIOD	10.6562 * 0.5
#define SATURN_ORBIT_RADIUS		9.58	* 0.5
#define SATURN_REVO_PERIOD		29.65	* 0.5

#define URANUS_EQUATOR_RADIUS	4.007	* 0.5
#define URANUS_ROTATION_PERIOD	-17.24  * 0.5
#define URANUS_ORBIT_RADIUS		19.22	* 0.35
#define URANUS_REVO_PERIOD		84.32	* 0.5

#define NEPTUNE_EQUATOR_RADIUS	3.829	* 0.5
#define NEPTUNE_ROTATION_PERIOD	16.11	* 0.5
#define NEPTUNE_ORBIT_RADIUS	30.10	* 0.25
#define NEPTUNE_REVO_PERIOD		164.79	* 0.5

#define PLUTO_EQUATOR_RADIUS	0.19
#define PLUTO_ROTATION_PERIOD	-153.29 * 0.5
#define PLUTO_ORBIT_RADIUS		39.48	* 0.23
#define PLUTO_REVO_PERIOD		248.09	


#endif //SOLARSYSTEM_CONFIG_H_