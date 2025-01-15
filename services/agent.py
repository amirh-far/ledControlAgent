from openai import OpenAI
import json


def gpt_chat_completion(prompt: str):
    client = OpenAI()

    system_prompt = """
    You are an assistant for an IoT system that controls LED lights. Based on the user's prompt, you must decide which function to call for controlling the lights. If you are asked to control multiple lights, provide the instructions in the list returned.
    A led corresponds to the kitchen light.
    B led corresponds to the room light.

    The function options are:
    A1: turning on the light number 1,
    A0: turning off the light number 1,
    B1: turning on the light number 2,
    B0: turning off the light number 2
    
    """

    tools = [{
        "type": "function",
        "function": {
            "name": "control_lights",
            "description": "Control the IoT LED lights based on the user's instructions. If the prompt requires multiple LED controls, provide them in the list returned.",
            "parameters": {
                "type": "object",
                "properties": {
                    "codes": {
                        "type": "array",
                        "items": {
                            "type": "string",
                            "enum": ["A1", "A0", "B1", "B0"]
                        }
                    }
                },
                "required": ["codes"],
                "additionalProperties": False
            },
            "strict": True
        }
    }]

    messages = [
        {
            "role": "system",
            "content": system_prompt
        },
        {
            "role": "user",
            "content": prompt
        }
    ]

    completion = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
        tools=tools
    )

    tool_calls = completion.choices[0].message.tool_calls[0]

    codes_json = tool_calls.function.arguments

    codes = json.loads(codes_json)

    with open("data.json", "w", encoding="utf-8") as f:
        json.dump(codes, f, ensure_ascii=False, indent=4)

    # print(codes_json)

    # print(completion.choices[0].message)
    # message = f"{completion.choices[0].message.content}"

    return codes
