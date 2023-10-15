from testEngine import test
import articFileUtils as fileUtils
import dbCreate
from dbParameterTable import parameterTableInterface

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
    test.endScenario("Create database and check writing the parameters")
    
def createAndLoadTestDatabase():
    dbCreate.createDatabase(path="/databases/test.sqlite")
    global testParameterTable
    testParameterTable = parameterTableInterface("/databases/test.sqlite")
    
def test11():
    testParameterTable.writeCycleTime(200)
    result = testParameterTable.readCycleTime()
    test.testIfEqual(200, result, "Cycle time written and read successfully")
    
def test12():
    testParameterTable.writeMasterNode(10)
    result = testParameterTable.readMasterNode()
    test.testIfEqual(10, result, "Master node written and read successfully")
    
def test13():
    testParameterTable.writePathToFiles("/test/path")
    result = testParameterTable.readPathToFiles()
    test.testIfEqual("/test/path", result, "Path to files written and read successfully")

def test14():
    result = testParameterTable.readVersion()
    test.testIfEqual(str(0.1), result, "Version read successfully")

if __name__ == "__main__":
    runTest()
    test.printResults()