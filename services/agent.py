from openai import OpenAI


def gpt_chat_completion(prompt: str):
    client = OpenAI()

    system_prompt = """
    You are an assistant for an IoT system that controls LED lights. Based on the user's prompt, you must decide which function to call for controlling the lights.
    The function options are:
    A1: turning on the light number 1,
    A0: turning off the light number 1,
    B1: turning on the light number 2,
    B0: turning off the light number 2
    
    """

    functions = [
        {
            "name": "control_lights",
            "description": "Control the IoT LED lights based on the user's instructions. If the prompt requires multiple led controls provide them in the list returned.",
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
                "required": ["codes"]
            }
        }
    ]

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
        functions=functions,
        function_call="auto"
    )

    print(completion.choices[0].message)
    message = f"{completion.choices[0].message.content}"
    return message
