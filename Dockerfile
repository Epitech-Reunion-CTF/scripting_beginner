FROM python

RUN mkdir /app
WORKDIR /app

COPY ./bin/server/main.py /app/main.py


RUN pip3 install gevent

CMD ["python", "/app/main.py"]
