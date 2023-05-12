FROM python

RUN mkdir /app
WORKDIR /app

COPY ./bin/server/server.py /app/server.py

EXPOSE 1028
EXPOSE 1536-2048

CMD ["python", "/app/server.py"]
