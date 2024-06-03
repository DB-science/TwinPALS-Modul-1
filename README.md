# TwinPALS Module 1: Digital Twin for Positron Annihilation Spectroscopy (PALS)

<p style="font-size:18px;">This first module of the digital twin for Positron Annihilation Spectroscopy (PALS) is a Geant4-based simulation written in C++. In this simulation, the positron source is simplified to only produce the accompanying gamma of 1275 keV energy and the two collinear 511 keV gamma quanta from annihilation. Each gamma energy requires its own simulation run. The scintillators available in this simulation are based on common plastic scintillators used in PALS applications.</p>

## Prerequisites

<p style="font-size:16px;">To successfully use this simulation, Geant4 must be downloaded in advance. The version I used is 11.0.0, which can be downloaded here: <a href="https://geant4.web.cern.ch/download/all">Geant4 Download</a>. A YouTube video detailing the installation and initial steps with Geant4 can be found at the following link: <a href="https://www.youtube.com/watch?v=Lxb4WZyKeCE&t=356s">Geant4 Installation Guide</a>.</p>

## How to Use the First Module of TwinPALS

<p style="font-size:16px;">In the <code>src</code> folder, you will find a file named <code>DetectorConstruction.cc</code>. Between lines 205 and 236, there is a marked section (see image below). This section contains several parameters that can be adjusted as needed.</p>

### Adjustable Parameters

<p style="font-size:16px;">
- <b>worldSizeXY</b> and <b>worldSizeZ</b>: Define the dimensions of the world volume.<br>
- <b>Scintillator_geometry_choice</b>: Switch between four different scintillator geometries by setting values from 0 to 3.<br>
- <b>cryst_dX, cryst_dY, cryst_dZ, Frontradius</b>: Determine the dimensions of the scintillators used.<br>
- <b>Distance_form_origin</b>: Specifies the distance of the scintillator surface from the center of the world volume.
</p>

<p style="font-size:16px;">Please refer to the image below for the exact location of these parameters in the <code>DetectorConstruction.cc</code> file. Adjust these parameters according to your specific requirements to tailor the simulation to your needs.</p>

![Einstellungen](https://github.com/DB-science/TwinPALS-Modul-1/assets/102671948/1e6d9982-0e47-41a4-9960-5ed58f4941ee)


<p style="font-size:16px;">Additionally, in the <code>src</code> folder, in the file <code>PrimaryGenerator.cc</code>, at line 44 (see image below), you can switch between the two gamma energies (511 keV collinear gamma quanta or 1275 keV) by setting the value to 1 or 0.</p>

![Einstellungen_Gamma_energy](https://github.com/DB-science/TwinPALS-Modul-1/assets/102671948/618c7d0e-c229-40de-b598-57e01321851e)

<p style="font-size:16px;">Finally, in the <code>src</code> folder, in the file <code>RunAction.cc</code>, at line 92, you define the location and name of the binary data stream within the quotation marks. The file extension .stream should be retained.</p>

![Einstellungen_StreamSave](https://github.com/DB-science/TwinPALS-Modul-1/assets/102671948/bec4bd9d-340e-417e-bc34-89db6d73b1a1)

# How to cite this Software? 
<p style="font-size:16px;">You must cite the applied version of this software in your study.
<p style="font-size:16px;">You can cite all versions by using the DOI 10.5281/zenodo.11448085. This DOI represents all versions, and will always resolve to the latest one
