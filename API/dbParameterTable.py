import sqliteEngine
from articLogger import log

class parameterTableInterface:
    def __init__(self, path="/databases/active.sqlite"):
        self.path = path
    
    def readVersion(self):
        DB = sqliteEngine.sqliteEngine(self.path)
        version = DB.readEntryFiltered("parameters", "value", "name='version'")[0][0]
        log.addEntry("Version of the database read as " + str(version))
        DB.commitClose()
        return version
    
    def readCycleTime(self):
        DB = sqliteEngine.sqliteEngine(self.path)
        cycleTime = DB.readEntryFiltered("parameters", "value", "name='cycleTime'")[0][0]
        log.addEntry("Cycle time of the system read as " + str(cycleTime) + "ms")
        DB.commitClose()
        return int(cycleTime)
    
    def readMasterNode(self):
        DB = sqliteEngine.sqliteEngine(self.path)
        masterNode = DB.readEntryFiltered("parameters", "value", "name='masterNode'")[0][0]
        log.addEntry("Master node of the system read as " + str(masterNode))
        DB.commitClose()
        return int(masterNode)
    
    def readPathToFiles(self):
        DB = sqliteEngine.sqliteEngine(self.path)
        pathToFiles = DB.readEntryFiltered("parameters", "value", "name='pathToFiles'")[0][0]
        log.addEntry("Path to files of the system read as " + str(pathToFiles))
        DB.commitClose()
        return pathToFiles
    
    def writeCycleTime(self, cycleTime):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("parameters", "value", str(cycleTime), "name='cycleTime'")
        log.addEntry("Cycle time of the system written as " + str(cycleTime) + "ms")
        DB.commitClose()
        
    def writeMasterNode(self, masterNode):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("parameters", "value", str(masterNode), "name='masterNode'")
        log.addEntry("Master node of the system written as " + str(masterNode))
        DB.commitClose()
        
    def writePathToFiles(self, pathToFiles):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("parameters", "value", f"'{str(pathToFiles)}'", "name='pathToFiles'")
        log.addEntry("Path to files of the system written as " + str(pathToFiles))
        DB.commitClose()
        
parameterTable = parameterTableInterface()