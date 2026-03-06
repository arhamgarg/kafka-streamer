# Kafka Streamer

This project provides a streamer for interacting with Apache Kafka using C, the `librdkafka` library, and `GLib`. It includes a producer application that generates synthetic stock trade data and a consumer application that consumes this data from a Kafka topic.

## Running the Applications

### 1. Run the Kafka Consumer

First, start the consumer to listen for messages. The consumer will connect to the `stock_trades` topic and print any consumed messages to the console. It will continuously wait for messages.

### 2. Run the Kafka Producer

In a separate terminal, run the producer to send synthetic stock trade events. The producer will generate 10 random stock trade messages and send them to the `stock_trades` topic. After sending the messages, the producer will exit.

You should see the messages appear in the consumer's terminal.
