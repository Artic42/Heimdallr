import uvicorn
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
import random

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins="*",
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE"],
    allow_headers=["*"],
)


@app.get("/")
def read_root():
    return {"Hello": "World"}

@app.get("/respond1")
def randomAnswer():
    randomNumber = random.randint(1,2)
    return {"code": randomNumber}

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)