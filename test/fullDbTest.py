from testEngine import test
import testCreateDatabase
import testDbNodeTable
import testDbParameterTable
import testDbPinTable

def runTest():
    testCreateDatabase.runTest()
    testDbNodeTable.runTest()
    testDbPinTable.runTest()
    testDbParameterTable.runTest()
    
    
if __name__ == "__main__":
    runTest()
    test.printResults()