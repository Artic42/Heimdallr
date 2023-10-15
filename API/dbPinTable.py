import sqliteEngine
from articLogger import log

class pinTableInterface:
    def __init__(self, path="/databases/active.sqlite"):
        self.path = path
        
    def readPin(self, pinID, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        result = DB.readEntryFiltered("pins", "*", f"pinNumber={pinID} AND node={nodeID}")[0]
        DB.commitClose()
        resultDict = {
            "pinNumber": result[0],
            "node": result[1],
            "active": result[2],
            "pinName": result[3],
            "pinDescription": result[4],
            "direction": result[5],
            "PWM": result[6],
            "edgeMode": result[7]}
        log.addEntry(f"Pin {pinID} read as:")
        log.addEntry(resultDict)
        return resultDict
        
    def deletePin(self, pinID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.deleteEntry("pins", f"pinNumber={pinID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} deleted")
        
    def createPin(self, pinID, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.addEntry("pins", "pinNumber, node", f"{pinID}, {nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} created")
        
    def activatePin(self, pinID, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "active", 1, f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} activated")
        
    def deactivatePin(self, pinID, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "active", 0, f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} deactivated")
        
    def updatePinName(self, pinID, nodeID, pinName):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "pinName", f"'{pinName}'", f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} name updated to {pinName}")
        
    def updatePinDescription(self, pinID, nodeID, pinDescription):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "pinDescription", f"'{pinDescription}'", f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} description updated to {pinDescription}")

    def updatePinDirection(self, pinID, nodeID, direction):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "direction", f"{direction}", f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} direction updated to {direction}")
        
    def updatePinPWM(self, pinID, nodeID, PWM):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "PWM", f"{PWM}", f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} PWM updated to {PWM}")
        
    def updatePinEdgeMode(self, pinID, nodeID, edgeMode):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("pins", "edgeMode", f"{edgeMode}", f"pinNumber={pinID} AND node={nodeID}")
        DB.commitClose()
        log.addEntry(f"Pin {pinID} edge mode updated to {edgeMode}")
        
    def listOfActivePins(self, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        result = DB.readEntryFiltered("pins", "pinNumber", f"node={nodeID} AND active=1")[0]
        activePins = result[4].split(",")
        activePins = [int(i) for i in activePins]
        log.addEntry(f"Active pins for node {nodeID} read as:")
        log.addEntry(activePins)
        return activePins
        