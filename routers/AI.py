from fastapi import APIRouter
import requests
import json

from schemas.AI import AI
from services.agent import gpt_chat_completion

router = APIRouter(prefix="/AI", tags=["AI"])


@router.post("/prompt")
def prompt(ai: AI):
    prompt = ai.prompt
    response = gpt_chat_completion(prompt)
    json_data = {
        "data": response
    }
    with open("data.json", "w", encoding="utf-8") as f:
        json.dump(json_data, f, ensure_ascii=False, indent=4)
    # esp32_ip = "192.168.47.162"
    # esp32_port = "80"
    # url = f"http://{esp32_ip}:{esp32_port}"
    # payload = {
    #     "data": response,
    # }
    # requests.post(url, json=payload)
    return {
        "Message": "Success",
        "gptResponse": response
    }
@router.get("/data")
def get_data():
    with open("data.json", "r", encoding="utf-8") as f:
        data = json.load(f)
    return data
