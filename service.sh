#!/bin/bash
uvicorn server:app \
 --host localhost \
 --port 7007 \
 --workers 1 