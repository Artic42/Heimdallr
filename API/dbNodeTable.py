import sqliteEngine
from articLogger import log


class nodeTableInterface:
    def __init__(self, path="/databases/active.sqlite"):
        self.path = path
    
    def readNode(self, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        node = DB.readEntryFiltered("nodes", "*", f"nodeNumber={nodeID}")[0]
        DB.commitClose()
        activePins = node[4].split(",")
        activePins = [int(i) for i in activePins]
        result = {
            "nodeNumber": node[0],
            "nodeIP": node[1],
            "nodeName": node[2],
            "nodeDescription": node[3],
            "activePins": activePins,
        }
        log.addEntry(f"Node {nodeID} read as:")
        log.addEntry(result)
        return result
    
    def createNode(self, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.addEntry("nodes", "nodeNumber", nodeID)
        DB.commitClose()
        log.addEntry(f"Node {nodeID} created")
        
    def deleteNode(self, nodeID):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.deleteEntry("nodes", f"nodeNumber={nodeID}")
        DB.commitClose()
        log.addEntry(f"Node {nodeID} deleted")
        
    def updateNodeIP(self, nodeID, nodeIP):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("nodes", "nodeIP", f"'{nodeIP}'", f"nodeNumber={nodeID}")
        DB.commitClose()
        log.addEntry(f"Node {nodeID} IP updated to {nodeIP}")
        
    def updateNodeName(self, nodeID, nodeName):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("nodes", "nodeName", f"'{nodeName}'", f"nodeNumber={nodeID}")
        DB.commitClose()
        log.addEntry(f"Node {nodeID} name updated to {nodeName}")
        
    def updateNodeDescription(self, nodeID, nodeDescription):
        DB = sqliteEngine.sqliteEngine(self.path)
        DB.updateEntry("nodes", "nodeDescription", f"'{nodeDescription}'", f"nodeNumber={nodeID}")
        DB.commitClose()
        log.addEntry(f"Node {nodeID} description updated to {nodeDescription}")
        
    def updateNodeActivePins(self, nodeID, activePins):
        DB = sqliteEngine.sqliteEngine(self.path)
        activePins = [str(i) for i in activePins]
        activePinsString = ",".join(activePins)
        DB.updateEntry("nodes", "activePins", f"'{activePinsString}'", f"nodeNumber={nodeID}")
        DB.commitClose()
        log.addEntry(f"Node {nodeID} active pins updated to {activePins}")
        
    def listOfNodes(self):
        DB = sqliteEngine.sqliteEngine(self.path)
        nodes = DB.readEntry("nodes", "nodeNumber")[0]
        DB.commitClose()
        log.addEntry(f"List of nodes read as {nodes}")
        return nodes
    