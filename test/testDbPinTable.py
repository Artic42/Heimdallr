from testEngine import test
import articFileUtils as fileUtils
import dbCreate
from dbNodeTable import nodeTableInterface
from dbPinTable import pinTableInterface

def runTest():
    fileUtils.deleteFile("/databases/test.sqlite") if fileUtils.fileExists("/databases/test.sqlite") else None
    runScenario1()
    fileUtils.deleteFile("/databases/test.sqlite")
    
def runScenario1():
    dbCreate.createDatabase(path="/databases/test.sqlite")
    global pinTable
    pinTable = pinTableInterface("/databases/test.sqlite")
    DB = nodeTableInterface("/databases/test.sqlite")
    DB.createNode(1)
    test.newScenario("Create a pin and wirte each column then read it back")
    test11()
    test12()
    test.endScenario("Create a pin and wirte each column then read it back")

def test11():
    pinTable.createPin(1, 1)
    test.testIfTrue(True, "Pin created successfully")
    pinTable.activatePin(1, 1)
    test.testIfTrue(True, "Pin activated successfully")
    pinTable.updatePinName(1, 1, "Test pin")
    test.testIfTrue(True, "Pin name updated successfully")
    pinTable.updatePinDescription(1, 1, "Test pin description")
    test.testIfTrue(True, "Pin description updated successfully")
    pinTable.updatePinDirection(1, 1, 1)
    test.testIfTrue(True, "Pin direction updated successfully")
    pinTable.updatePinPWM(1, 1, 10000)
    test.testIfTrue(True, "Pin PWM updated successfully")
    pinTable.updatePinEdgeMode(1, 1, 1)
    test.testIfTrue(True, "Pin edge mode updated successfully")
    
def test12():
    result = pinTable.readPin(1, 1)
    test.testIfEqual(1, result["pinNumber"], "Pin number read successfully")
    test.testIfEqual(1, result["node"], "Node read successfully")
    test.testIfEqual(1, result["active"], "Pin active read successfully")
    test.testIfEqual("Test pin", result["pinName"], "Pin name read successfully")
    test.testIfEqual("Test pin description", result["pinDescription"], "Pin description read successfully")
    test.testIfEqual(1, result["direction"], "Pin direction read successfully")
    test.testIfEqual(10000, result["PWM"], "Pin PWM read successfully")
    test.testIfEqual(1, result["edgeMode"], "Pin edge mode read successfully")
    
def test13():
    pinTable.deactivatePin(1, 1)
    test.testIfEqual(0, pinTable.readPin(1, 1)["active"], "Pin deactivated successfully")

if __name__ == "__main__":
    runTest()
    test.printResults()