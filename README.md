# Radiation Dosimeter for Space Radiation Environment (SRE)

## Objective
Using the 3-d Monte Carlo particle transport toolkit, Geant4, a simple detector concept for a charged particle telescope to study space radiation environment is simulated.

## Rationale
The hostile radiation environment outside the Earth’s cocoon is both complex and dynamic. The space radiation comprises of charged particles: trapped in the van Allen belts, those shot into space during violent solar events; and the ones constituting the galactic cosmic rays. The charged particles suffer ionization losses when traversed through a material. The energy absorbed in the material due to the ionized radiation is a measure to assess several radiation risks. Estimating the radiation risk to the onboard crew and instruments is coined under the term, “radiation dosimetry”. The variations in time of particle fluxes and their localization in the orbit of a spacecraft presents a need for continuous measurements of the radiation environment during the mission and provide real-time data to assess the in-flight safety of the crew and for the protection of the scientific equipments and material. 

## Geant4 toolkit
[Geant4](https://geant4.web.cern.ch/) (Geometry ANd Tracking) developed by a large international collaboration including CERN, ESA, and many other institutes and universities. It is based on object-orienteda analysis and design methodology by [Grady Booch [1994]](https://dl.acm.org/doi/book/10.5555/174890), and its applications range from high-energy physics, medical physics to space physics and engineering. Some of the features of Geant4 which makes it stand apart from other particle transport toolkit are facilities for handling complex geometry, wide range of physics processes included, detector response and some of simulation properties like tracking and run management as well as visualization and user interface. Geant4 offers flexibility by allowing users to select (multiple) physics models of particle interaction appropriate for a desired problem thereby taking care of all relevant interactions for all participating particles, including the secondaries, in the simulation.

## Detector geometry
The proposed design for the charged particle telescope uses solid state detectors. The configuration consists of two Si P-I-N photodiodes (0.3 mm thick and area 4 cm2) separated by a high Z absorber (lead here, 5 mm thick) in a telescopic arrangement. Inclusion of the sandwiched lead plate allows a substantial difference in the energy of the particle incident on the photodiode below it such that the energies deposited in both the photodiodes are distinct. The main objectives behind this design is to detect individual charge particle interacting with the detectors, identify particle type from the total energy deposited in the detectors as well as to measure energy of the incident particle from difference between the energy deposited in the two detectors. The entire setup is enclosed in an aluminum box (8mm thick). 

![detgeom](https://github.com/jayantpendharkar/G4RadiationDosimeterSRE/blob/master/dosi_detgeom.png)

## What I did ...
Markup :	1. Created Detector geometry
		2. analysis using iDL and R

 Markup : 1. A numbered list
              1. A nested numbered list
              2. Which is numbered
          2. Which is numbered

