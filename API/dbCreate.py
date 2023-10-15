import sqliteEngine
import sys

def createDatabase(path="/databases/active.sqlite"):
    global databaseVersionNumber
    databaseVersionNumber = 0.1
    global database
    database = sqliteEngine.sqliteEngine(path)
    createParametersTable()
    createNodesTable()
    createPinsTable()
    database.commitClose()
    
def createParametersTable():
    database.createTable("parameters", "name TEXT UNIQUE, value TEXT")
    database.addEntry("parameters", "name, value", "'version', '" + str(databaseVersionNumber) + "'")
    database.addEntry("parameters", "name, value", "'cycleTime', '100'")
    database.addEntry("parameters", "name, value", "'masterNode', 'none'")
    database.addEntry("parameters", "name, value", "'pathToFiles', 'none'")
    
def createNodesTable():
    
    database.createTable("nodes", 
                         "nodeNumber INTEGER UNIQUE PRIMARY KEY, nodeIP TEXT, nodeName TEXT, nodeDescription TEXT,activePins TEXT")

def createPinsTable():
    database.createTable("pins",
                         "pinNumber INTEGER PRIMARY KEY, node INTEGER, active INTEGER, pinName TEXT, pinDescription TEXT, direction INTEGER, PWM INTEGER, edgeMode INTEGER, FOREIGN KEY(node) REFERENCES nodes(nodeNumber)")
                         

if __name__ == "__main__":
    if len(sys.argv) == 1:
        path = "/databases/active.sqlite"
    else:
        path = sys.argv[1]
    createDatabase(path=path)
