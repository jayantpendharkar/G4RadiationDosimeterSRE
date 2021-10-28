# Radiation Dosimeter for Space Radiation Environment (SRE)

## Objective
Using the 3-d Monte Carlo particle transport toolkit, Geant4, a simple detector concept for a charged particle telescope to study space radiation environment is simulated.

## Rationale
The hostile radiation environment outside the Earth’s cocoon is both complex and dynamic. The space radiation comprises of charged particles: trapped in the van Allen belts, those shot into space during violent solar events; and the ones constituting the galactic cosmic rays. The charged particles suffer ionization losses when traversed through a material. The energy absorbed in the material due to the ionized radiation is a measure to assess several radiation risks. Estimating the radiation risk to the onboard crew and instruments is coined under the term, “radiation dosimetry”. The variations in time of particle fluxes and their localization in the orbit of a spacecraft presents a need for continuous measurements of the radiation environment during the mission and provide real-time data to assess the in-flight safety of the crew and for the protection of the scientific equipments and material. 

## Detector geometry
The proposed design for the charged particle telescope uses solid state detectors. The configuration consists of two Si P-I-N photodiodes (0.3 mm thick and area 4 cm2) separated by a high Z absorber (lead here, 5 mm thick) in a telescopic arrangement. Inclusion of the sandwiched lead plate allows a substantial difference in the energy of the particle incident on the photodiode below it such that the energies deposited in both the photodiodes are distinct. The main objectives behind this design is to detect individual charge particle interacting with the detectors, identify particle type from the total energy deposited in the detectors as well as to measure energy of the incident particle from difference between the energy deposited in the two detectors. The entire setup is enclosed in an aluminum box (8mm thick). 
![detgeom](https://github.com/jayantpendharkar/G4RadiationDosimeterSRE/blob/master/dosi_detgeom.png)


