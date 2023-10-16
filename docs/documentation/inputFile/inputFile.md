# The Input File {#inputFile}

[TOC]

## General

The concept of the input file is based on the definition of so-called "commands". A command in the input file can have one of the two following forms and is always case-insensitive:

    1) key = value;
    2) key = [value1, value2, ...];

<span style="color:red"><b>Note</b></span>: The semicolon add the end of both command definitions is necessary, while the number of whitespace can be arbitrary at any position of the command as long as key and value are not split in parts.

Command definition 1) represents a single value command, whereas definition 2) can be considered as a list of input values to which will always be represented with `[]`.

#### Command Usage
Due to the use of `;` one line of the input file can contain multiple commands and blank lines will be ignored.

#### Comments
Every character following a `#` will be ignored. The `#` as a comment flag can be used also in all setup files - with some exceptions when contiguous input blocks are necessary.

#### Types of Input Values
In the following sections the types of the input values will be denoted via `{}`, where `{[]}` represents a list of types:

<div align="center">

|    Type    |          Description          |
| :--------: | :---------------------------: |
|   {int}    |            integer            |
|  {uint+}   |       positive integers       |
|   {uint}   | positive integers including 0 |
|  {double}  |    floating point numbers     |
|  {string}  |               -               |
|   {file}   |               -               |
|   {path}   |               -               |
| {pathFile} |     equal to {path/file}      |
|   {bool}   |          true/false           |

</div>

## Input Keys
<span style="color:red"><b>Note</b></span>:: Some of the following keys are necessary in the input file and are therefore marked with a `*`. If there exists a default value for the possible values related to a key, they will be marked with `->` after the command.

### General Keys

#### Jobtype


    jobtype* = {string} 

>   With the `jobtype` keyword the user can choose out of different engines to perform (not only) MD simulations.
    
>  <ins>Possible values are:</ins>

>>    1) <b>mm-md</b> - represents a full molecular mechanics molecular dynamics simulation either performed via the `Guff` formalism or the `Amber force field`


>>    2) <b>qm-md</b> - represents a full quantum mechanics molecular dynamics simulation. For more information see the [QM](#qmKeywords) keywords section.


>>    3) <b>qm-rpmd</b> - represents a full quantum mechanics ring polymer molecular dynamics simulation. For more information see the [Ring Polymer MD](#ringPolymerMD) keywords section


#### Timestep

    timestep* = {double} fs

>   With the `timestep` keyword the time step in `fs` of one molecular dynamics loop can be set.

#### NStep

    nstep* = {uint+}

>   This keyword sets the total amount of MD steps to be performed within the next simulation run.

#### Integrator

    integrator = {string} -> "v-verlet"

>   With the `integrator` keyword the user can choose the integrator type which should be applied.

>   Possible options are:

>>   1) <b>v-verlet</b> (default) - represents the Velocity-Verlet integrator 

#### Virial

    virial = {string} -> "molecular"

>   With the `virial` keyword the user can control if an intramolecular virial correction should be applied on the basis of molecular units definitions form the moldescriptor file.

>   Possible options are:

>>  1) <b>molecular</b> (default) - to the resulting virial from the force contributions an intramolecular correction will be applied.

>>  2) <b>atomic</b> - no intramolecular correction to the resulting virial will be applied

#### Start_File

    start_file* = {file}

>   The `start_file` keyword sets the name of the start file for an MD simulation of any kind.

#### RPMD_Start_File

    rpmd_start_file = {file}

>   The `rpmd_start_file` keyword is used to continue a ring polymer MD simulation containing positions, velocities and forces of all atoms of each bead of the ring polymer.

### General Output Keys

<span style="color:red"><b>Note</b></span>: The PIMD-QMCF application has a special naming convention for output files. For every job type a certain set of output files is written per default. If no output file names are given all prefixes of the output files will be named `default.<ext>`. If at least one of the output file keys was given in the input file - the program will determine the most common prefix (*i.e.* string before the first `.` character) and set it with the respective extension for all unspecified output files.

This feature enables easier post-processing of data and also easier deletion of all output files as PIMD-QMCF does not overwrite any existing output files and will throw an error.

#### Output_Freq

    output_freq = {uint} -> 1

>   The `output_freq` keyword sets the frequency (*i.e.* every n-th step) of how often the application should write into the output files. For a complete dry run without any output files it is also possible to set it to `0`.

>   *default value* = 1

#### File_Prefix

    file_prefix = {string}

>   The `file_prefix` keyword allows the user to set a common prefix name for all generated output files. The resulting names of the output files should be self-explanatory according to their unique file extension.

#### Output_File

    output_file = {file} -> "default.out"

>   The `output_file` keyword sets the name for the log file, in which all important information about the performed calculation can be found. 

>   *default value* = "default.out"

### MD Output File Keys

All of the following output files presented in the MD Output Files section are wriiten during calculations using MD related jobtypes.

#### Info_File

    info_file = {file} -> "default.info"

>   The `info_file` keyword sets the name for the info file, in which the most important physical properties of the last written step can be found.

>   *default value* = "default.info"

#### Energy_File

    energy_file = {file} -> "default.en"

>   The `energy_file` keyword sets the name for the energy file, in which the (almost) all important physical properties of the full simulation can be found.

>   *default value* = "default.en"

#### Rst_File

    rst_file = {file} -> "default.rst"

>   The `rst_file` keyword sets the name for the restart file, which contains all necessary information to restart (*i.e.* continue) the calculation from its timestamp.

>   *default value* = "default.rst"

#### Traj_File

    traj_file = {file} -> "default.xyz"

>   The `traj_file` keyword sets the name for the trajectory file of the atomic positions.

>   *default value* = "default.xyz"

#### Vel_File

    vel_file = {file} -> "default.vel"

>   The `vel_file` keyword sets the name for the trajectory file of the atomic velocities.

>   *default value* = "default.vel"

#### Force_File

    force_file = {file} -> "default.force"

>   The `force_file` keyword sets the name for the trajectory file of the atomic forces.

>   *default value* = "default.force"

#### Charge_File

    charge_file = {file} -> "default.chrg"

>   The `charge_file` keyword sets the name for the trajectory file of the atomic partial charges.

>   *default value* = "default.chrg"

### RPMD Output File Keys

All of the following output files presented in the RPMD Output Files section are wriiten during calculations using ring polymer MD related jobtypes. These files represents the trajectories of all individual beads.

#### RPMD_Restart_File

    rpmd_restart_file = {file} -> "default.rpmd.rst"

>   The `rpmd_restart_file` keyword sets the name for the ring polymer restart file, which contains all necessary information to restart (*i.e.* continue) the calculation from its timestamp.

>   *default value* = "default.rpmd.rst"

#### RPMD_Traj_File

    rpmd_traj_file = {file} -> "default.rpmd.xyz"

>   The `rpmd_traj_file` keyword sets the name for the file containing positions of all atoms of each bead of the ring polymer trajectory.

>   *default value* = "default.rpmd.xyz"

#### RPMD_Vel_File

    rpmd_vel_file = {file} -> "default.rpmd.vel"

>   The `rpmd_vel_file` keyword sets the name for the file containing velocities of all atoms of each bead of the ring polymer trajectory.

>   *default value* = "default.rpmd.vel"

#### RPMD_Force_File

    rpmd_force_file = {file} -> "default.rpmd.force"

>   The `rpmd_force_file` keyword sets the name for the file containing forces of all atoms of each bead of the ring polymer trajectory.

>   *default value* = "default.rpmd.force"

#### RPMD_Charge_File

    rpmd_charge_file = {file} -> "default.rpmd.chrg"

>   The `rpmd_charge_file` keyword sets the name for the file containing partial charges of all atoms of each bead of the ring polymer trajectory.

>   *default value* = "default.rpmd.chrg"

#### RPMD_Energy_File

    rpmd_energy_file = {file} -> "default.rpmd.en"

>   The `rpmd_energy_file` keyword sets the name for the file containing relevant energy data for each ring polymer bead of the simulation.

>   *default value* = "default.rpmd.en"

### Input File Keys {#inputFileKeys}

In order to setup certain calculations additional input files have to be used. The names of these files have to be specified in the input file. For further information about these input files can be found in the [Setup Files]{#setupFiles} section.

#### Moldesctiptor_File

    moldescriptor_file = {file} -> "moldescriptor.dat"

>   *default value* = "moldescriptor.dat"

#### Guff_File

    guff_file = {file} -> "guff.dat"

>   *default value* = "guff.dat"

#### Topology_File

    topology_file = {file}

#### Parameter_File

    parameter_file = {file}

#### Intra-NonBonded_File

    intra-nonbonded_file = {file}

### Simulation Box Keys

#### Density

    density = {double} kgL⁻¹

>   With the `density` keyword the box dimension of the system can be inferred from the total mass of the simulation box.

>   <span style="color:red"><b>Note</b></span>: This keyword implies that the simulation box has cubic shape. Furthermore, the `density` keyword will be ignored if in the start file of a simulation any box information is given.

#### RCoulomb

<pre class="fragment">
rcoulomb = {double} &Aring; -> 12.5 &Aring;
</pre>


>   With the `rcoulomb` keyword the radial cut-off in &Aring; of Coulomb interactions for MM-MD type simulations can be set. If pure QM-MD type simulations are applied this keyword will be ignored and the value will be set to 0 &Aring;.

>   *default value* = 12.5 &Aring; (for MM-MD type simulations)

#### Init_Velocities

    init_velocities = {bool} -> false

>   To initialize the velocities of the system according to the target temperature with a Boltzmann distribution the user has to set the `init_velocities` to true.

>   Possible values are:

>>  1) <b>false</b> (default) - velocities are taken from start file

>>  2) <b>true</b> - velocities are initialized according to a Boltzmann distribution at the target temperature.

### Temperature Coupling Keys

#### Temperature

    temperature = {double} K

>   With the `temperature` keyword the target temperature in `K` of the system can be set. 

>   <span style="color:red"><b>Note</b></span>: This keyword is not restricted to the use of any temperature coupling method, as it is used *e.g.* also for the initialization of Boltzmann distributed velocities or the reset of the system temperature.

#### Thermostat
<!-- TODO: reference manual-->

    thermostat = {string} -> "none"

>   With the `thermostat` keyword the temperature coupling method can be chosen.

> Possible values are:

>>   1) <b>none</b> (default) - no thermostat is set, hence {N/µ}{p/V}E settings are applied.

>>   2) <b>berendsen</b> - the Berendsen weak coupling thermostat

>>   3) <b>velocity_rescaling</b> - the stochastic velocity rescaling thermostat

>>   4) <b>langevin</b> - temperature coupling <i>via</i> stochastic Langevin dynamics

>>   5) <b>nh-chain</b> - temperature coupling <i>via</i> Nose Hoover extended Lagrangian 

#### T_Relaxation

This keyword is used in combination with the Berendsen and velocity rescaling thermostat.

    t_relaxation = {double} ps -> 0.1 ps

>   With the `t_relaxation` keyword the relaxation time in `ps` (*i.e.* &tau;) of the Berendsen or stochastic velocity rescaling thermostat is set.

> *default value* = 0.1 ps

#### Friction

    friction = {double} ps⁻¹ -> 0.1 ps⁻¹

>   With the `friction` keyword the friction in `ps⁻¹` applied in combination with the Langevin thermostat can be set.

>   *default value* = 0.1 ps⁻¹

#### NH-Chain_Length

    nh-chain_length = {uint+} -> 3

> With the `nh-chain_length` keyword the length of the chain for temperature control *via* an extended Nose-Hoover Lagrangian can be set.

>   *default value* = 3

#### Coupling_Frequency

    coupling_frequency = {double} cm⁻¹ -> 1000 cm⁻¹

>   With the `coupling_frequency` keyword the coupling frequency of the Nose-Hoover chain in `cm⁻¹` can be set.

>   *default value* = 1000 cm⁻¹

### Pressure Coupling Keys

#### Pressure

    pressure = {double} bar

>   With the `pressure` keyword the target pressure in `bar` of the system can be set. 

>   <span style="color:red"><b>Note</b></span>: This keyword is only used if a manostat for controlling the pressure is explicitly define.

#### Manostat
<!-- TODO: reference manual-->

    manostat = {string} -> "none"

>   With the `manostat` keyword the type of the pressure coupling can be chosen.

>   Possible values are:

>>   1) <b>none</b> (default) - no pressure coupling is applied (*i.e.* constant volume)

>>   2) <b>berendsen</b> - Berendsen weak coupling manostat

>>   3) <b>stochastic_rescaling</b> - stochastic cell rescaling manostat

#### P_Relaxation

This keyword is used in combination with the Berendsen and stochastic cell rescaling manostat.

    p_relaxation = {double} ps -> 0.1 ps

>   With the `p_relaxation` keyword the relaxation time in `ps` (*i.e.* &tau;) of the Berendsen or stochastic cell rescaling manostat is set.

> *default value* = 0.1 ps

#### Compressibility

This keyword is used in combination with the Berendsen and stochastic cell rescaling manostat.

    compressibility = {double} bar⁻¹ -> 4.591e-5 bar⁻¹

>   With the `compressibility` keyword the user can specify the compressibility of the target system in `bar⁻¹` for the Berendsen and stochastic cell rescaling manostat.

>   *default value* = 4.591e-5 bar⁻¹ (compressibility of water)

#### Isotropy

    isotropy = {string} -> "isotropic"

>   With the `isotropy` keyword the isotropy of the pressure coupling for all manostat types is controlled.

>   Possible values are:

>>  1) <b>isotropic</b> (default) - all axes are scaled with the same scaling factor

>>  2) <b>xy</b> - semi-isotropic settings, with axes `x` and `y` coupled isotropic

>>  3) <b>xz</b> - semi-isotropic settings, with axes `x` and `z` coupled isotropic

>>  4) <b>yz</b> - semi-isotropic settings, with axes `y` and `z` coupled isotropic

>>  5) <b>anisotropic</b> - all axes are coupled in an anisotropic way

### Reset Kinetics Keys

#### NScale

    nscale = {uint} -> 0

>   With the `nscale` keyword the user can specify the first `n` steps in which the temperature is reset *via* a hard scaling approach to the target temperature.

> <span style="color:red"><b>Note</b></span>: Resetting the temperature to the target temperature does imply also a subsequent reset of the total box momentum. Furthermore, resetting to the target temperature does not necessarily require a constant temperature ensemble setting.

> *default value* = 0 (*i.e.* never)

#### FScale

    fscale = {uint} -> nstep + 1

>   With the `fscale` keyword the user can specify the frequency `f` at which the temperature is reset *via* a hard scaling approach to the target temperature.

> <span style="color:red"><b>Note</b></span>: Resetting the temperature to the target temperature does imply also a subsequent reset of the total box momentum. Furthermore, resetting to the target temperature does not necessarily require a constant temperature ensemble setting.

> *default value* = nstep + 1 (*i.e.* never)

> *special case* = 0 -> nstep + 1 

#### NReset

    nreset = {uint} -> 0

>   With the `nreset` keyword the user can specify the first `n` steps in which the total box momentum is reset.

> *default value* = 0 (*i.e.* never)

#### FReset

    freset = {uint} -> nstep + 1

>   With the `freset` keyword the user can specify the frequency `f` at which the total box momentum is reset.

> *default value* = nstep + 1 (*i.e.* never)

> *special case* = 0 -> nstep + 1

#### NReset_Angular

    nreset_angular = {uint} -> 0

>   With the `nreset_angular` keyword the user can specify the first `n` steps in which the total angular box momentum is reset.

> <span style="color:red"><b>Attention</b></span>: This setting should be used very carefully, since in periodic system a reset of the angular momentum can result in some very unphysical behavior.

> *default value* = 0 (*i.e.* never)

#### FReset_Angular

    freset_angular = {uint} -> nstep + 1

>   With the `freset_angular` keyword the user can specify the frequency `f` at which the total angular box momentum is reset.

> <span style="color:red"><b>Attention</b></span>: This setting should be used very carefully, since in periodic system a reset of the angular momentum can result in some very unphysical behavior.

> *default value* = nstep + 1 (*i.e.* never)

> *special case* = 0 -> nstep + 1 

### Constraints Keys

#### Shake

    shake = {string} -> "off"

>   With the `shake` keyword it is possible to activate the SHAKE/RATTLE algorithm for bond constraints.

>   Possible values are:

>>      1) <b>off</b> (default) - no shake will be applied

>>      2) <b>on</b> - shake for bond constraints defined in the [topology file](#topology_file) will be applied.

#### Shake-Tolerance

    shake-tolerance = {double} -> 1e-8

>   With the `shake-tolerance` keyword the user can specify the tolerance, with which the bond-length of the shaked bonds should converge.

> *default value* = 1e-8

#### Shake-Iter

    shake-iter = {uint+} -> 20

>   With the `shake-iter` keyword the user can specify the maximum number of iteration until the convergence of the bond-lengths should be reached within the shake algorithm.

> *default value* = 20

#### Rattle-Tolerance


    rattle-tolerance = {double} s⁻¹kg⁻¹ -> 1e4 s⁻¹kg⁻¹ 


>   With the `rattle-tolerance` keyword the user can specify the tolerance in `s⁻¹kg⁻¹`, with which the velocities of the shaked bonds should converge.

> *default value* = 20 s⁻¹kg⁻¹

#### Rattle-Iter

    rattle-iter = {uint+} -> 20

>   With the `rattle-iter` keyword the user can specify the maximum number of iteration until the convergence of the velocities of the shaked bond-lengths should be reached within the rattle algorithm.

> *default value* = 20

### MM Keys {#mmKeywords}

#### NonCoulomb

    noncoulomb = {string} -> "guff"

>   With the `noncoulomb` keyword the user can specify which kind of [GUFF formalism](#guffdatFile) should be used for parsing the guff.dat input file. <span style="color:red"><b>Note</b></span>: This keyword is only considered if an MM-MD type simulation is requested and the force field is not turned on.

>   Possible options are:

>>  1) <b>guff</b> (default) - full GUFF formalism

>>  2) <b>lj</b> - Lennard Jones quick routine

>>  3) <b>buck</b> - Buckingham quick routine

>>  4) <b>morse</b> - Morse quick routine

#### ForceField

    forcefield = {string} -> "off"

>   With the `forcefield` keyword the user can switch from the GUFF formalism to force field type simulation (For details see Reference Manual).

>   Possible options are:

>>  1) <b>off</b> (default) - GUFF formalism is applied

>>  2) <b>on</b> - full force field definition is applied

>>  3) <b>bonded</b> - non bonded interaction are described *via* GUFF formalism and bonded interactions *via* force field approach

### Long Range Correction

#### Long_Range

    long_range = {string} -> "none"

>   With the `long_range` correction keyword the user can specify the type of <b>Coulombic<B> long range correction, which should be applied during the Simulation.

>   Possible options are:

>>  1) <b>none</b> (default) - no long range correction

>>  2) <b>wolf</b> - Wolf summation

#### Wolf_Param

<!-- TODO: add unit and description-->
    wolf_param = {double} -> 0.25 

>   *default value* = 0.25

### QM Keys {#qmKeywords}

#### QM_PROG

    qm_prog = {string}

>   With the `qm_prog` keyword the external QM engine for any kind of QM MD simulation is chosen.

>   <span style="color:red"><b>Note</b></span>: This keyword is required for any kind of QM MD simulation!

>   Possible values are:

>>  1) <b>dftbplus</b>

>>  2) <b>pyscf</b>

>>  3) <b>turbomole</b>

#### QM_SCRIPT

    qm_script = {file}

>   With the `qm_script` keyword the external executable to run the QM engine and to parse its output is chosen. All possible scripts can be found under https://github.com/97gamjak/pimd_qmcf/tree/main/src/QM/scripts. Already the naming of the executables should hopefully be self-explanatory in order to choose the correct input executable name.

### Ring Polymer MD Keys {#ringPolymerMD}

#### RPMD_n_replica

    rpmd_n_replica = {unit+}

>   With the `rpmd_n_replica` keyword the number of beads for a ring polymer MD simulation is controlled.

>   <span style="color:red"><b>Note</b></span>: This keyword is required for any kind of ring polymer MD simulation!

### Cell List Keys

#### Cell-List

    cell-list = {string} -> "off"

>   With the `cell-list` the user can activate a cell-list approach to calculate the pair-interactions in MM-MD simulations (no effect in pure QM-MD type simulations).

>   Possible options are:

>>  1) <b>off</b> (default) - brute force routine

>>  2) <b>on</b> - cell list approach is applied

#### Cell-Number

    cell-number = {uint+} -> 7

>   With the `cell-number` keyword the user can set the number of cells in each direction in which the simulation box will be split up (*e.g.* cell-number = 7 -> total cells = 7x7x7)

>   *default value* = 7