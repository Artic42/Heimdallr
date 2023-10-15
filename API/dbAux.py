import sqliteEngine

def openDatabase(path):
    return sqliteEngine.sqliteEngine(path)