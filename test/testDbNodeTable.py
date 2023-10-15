from testEngine import test
import articFileUtils as fileUtils
import sqliteEngine
import dbCreate
from dbNodeTable import nodeTableInterface

def runTest():
    fileUtils.deleteFile("/databases/test.sqlite") if fileUtils.fileExists("/databases/test.sqlite") else None
    runScenario1()
    fileUtils.deleteFile("/databases/test.sqlite")

def runScenario1():
    test.newScenario("Create database and check writing the parameters")
    createAndLoadTestDatabase()
    test11()
    test12()
    test13()
    test14()
    test15()
    test16()
    test.endScenario("Create database and check writing the parameters")
    
def createAndLoadTestDatabase():
    dbCreate.createDatabase(path="/databases/test.sqlite")
    global testParameterTable
    testParameterTable = nodeTableInterface("/databases/test.sqlite")
    
def test11():
    testParameterTable.createNode(1)
    test.testIfTrue(True, "Node created successfully")
    
def test12():
    testParameterTable.updateNodeIP(1, "192.168.1.10")
    test.testIfTrue(True, "Node IP updated successfully")
    
def test13():
    testParameterTable.updateNodeName(1, "Test node")
    test.testIfTrue(True, "Node name updated successfully")
    
def test14():
    testParameterTable.updateNodeDescription(1, "Test node description")
    test.testIfTrue(True, "Node description updated successfully")
    
def test15():
    testParameterTable.updateNodeActivePins(1, [1,2,3,4,5,6,7,8,9,10])
    test.testIfTrue(True, "Node active pins updated successfully")
    
def test16():
    result = testParameterTable.readNode(1)
    test.testIfEqual(1, result["nodeNumber"], "Node number read successfully")
    test.testIfEqual("192.168.1.10", result["nodeIP"], "Node IP read successfully")
    test.testIfEqual("Test node", result["nodeName"], "Node name read successfully")
    test.testIfEqual("Test node description", result["nodeDescription"], "Node description read successfully")
    test.testIfEqual([1,2,3,4,5,6,7,8,9,10], result["activePins"], "Node active pins read successfully")

if __name__ == "__main__":
    runTest()
    test.printResults()