
from testEngine import test
import articFileUtils as fileUtils
import sqliteEngine
import dbCreate



def runTest():
    runScenario1()
    fileUtils.deleteFile("/databases/test.sqlite")

def runScenario1():
    test.newScenario("Create database and check all column exist")
    runCreateDatabase()
    test12()
    test13()
    test14()
    test.endScenario("Create database and check all column exist")

def runCreateDatabase():
    dbCreate.createDatabase(path="/databases/test.sqlite")
    global database 
    database = sqliteEngine.sqliteEngine("/databases/test.sqlite")
    test.testIfTrue(True, "Database created successfully")

def test12():
    database.addEntry("parameters", "name, value", "'test', 'test'")
    result = database.readEntryFiltered("parameters", "value", "name='test'")[0][0]
    test.testIfEqual("test", result, "Entry added and read successfully on table parameters")

def test13():
    database.addEntry("nodes", "nodeNumber, nodeIP, nodeName, nodeDescription, activePins", "10, '192.168.1.10', 'testNode', 'testNodeDescription', '1,2,3'")
    result = database.readEntryFiltered("nodes", "nodeIP", "nodeNumber=10")[0][0]
    test.testIfEqual("192.168.1.10", result, "Entry added and read successfully on table nodes")
    
def test14():
    database.addEntry("pins", "pinNumber, node, pinName, pinDescription, direction, PWM, edgeMode", "1, 10, 'testPin', 'testPinDescription', 1, 0, 0")
    result = database.readEntryFiltered("pins", "pinName", "pinNumber=1")[0][0]
    test.testIfEqual("testPin", result, "Entry added and read successfully on table pins")

if __name__ == "__main__":
    runTest()
    test.printResults()