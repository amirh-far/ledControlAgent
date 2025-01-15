from fastapi import APIRouter
import requests
import json

from schemas.AI import AI
from schemas.log import log
from services.agent import gpt_chat_completion

router = APIRouter(prefix="/AI", tags=["AI"])


@router.post("/prompt")
def prompt(ai: AI):
    prompt = ai.prompt
    codes = gpt_chat_completion(prompt)
    # esp32_ip = "192.168.47.162"
    # esp32_port = "80"
    # url = f"http://{esp32_ip}:{esp32_port}"
    # payload = {
    #     "data": response,
    # }
    # requests.post(url, json=payload)

    return {
        "Message": "Success",
        "gptResponse": codes
    }

@router.get("/data")
def get_data():
    with open("data.json", "r", encoding="utf-8") as f:
        data = json.load(f)
    return data

@router.post("/log")
def log(log: log):
    log = log.dict()
    with open("log.json", "w") as f:
        json.dump(log, f, ensure_ascii=False, indent=4)
    return {"Message": "Success"}
