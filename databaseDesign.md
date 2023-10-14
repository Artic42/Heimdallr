# Database Design Document

This is the definition of the database used to store the full configuration of the system. The system will store the database in the /databases folder of the webserver container. The database been edited on that moment will be store on the /database/active.sql file. The database will use sqlite.

## Tables

- __Parameters__: A table to store general parameter of the system
- __Nodes__: A table with the parameters of every node in the system
- __Pins__: A table with the parameters of every pin in every node

### Parameters

This are general parameter required by the system. The table has two columns, parameter and name. This are the existing parameters.

- Version
- Cycle Time
- Master node
- PathToFiles

### Nodes

This table stores the information of every node. It has the following columns

Column | Data type | isUnique | Description
-- | -- | -- | --
nodeNumber | Integer | True | Number to indetified the node
nodeIP | String | True | Ip of the node
nodeName | String | False | Name of the node, _only visible in configurator_
nodeDescription | String | False | Description of the node, _only visible in configurator_
activePins | String | False | List of active pins on the nodes

### Pins

This table stores the information of every pin. It has the following columns

Column | Data type | Description
-- | -- | -- | --
pinNumber | Integer | Pin number it corresponds to rapsbrrey pi GPIOX number
node | Integer | Node of the pin, identifier is node number
direction | Integer | Integer value representing the direction of the pin, see below
pullResistor | Integer | Integer value representing the mode of the pull resistor, see below
PWM | Integer | Frequency of the PWM if in output mode. 0 will disable the PWM
edgeMode | Integer | Integer value representing the mode of the edge mode, see below

#### Direction

Status | Value
-- | --
Input | 1
Output | 2
Comms | 3

#### Pull resistor

Status | Value
-- | --
Deactivated | 0
Pull Up | 1
Pull Down | 2
Both | 3

#### Edge mode

Status | Value
-- | --
Desctivated | 0
Raising Edge | 1
Falling Edge | 2
Both | 3