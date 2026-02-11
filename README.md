# Kafka Streamer

This project provides a streamer for interacting with Apache Kafka using C, the `librdkafka` library, and `GLib`. It includes a producer application that generates synthetic stock trade data and a consumer application that consumes this data from a Kafka topic.

## Features

*   **Kafka Producer:** Demonstrates how to produce messages to a Kafka topic.
*   **Kafka Consumer:** Demonstrates how to consume messages from a Kafka topic.
*   **C-based Implementation:** Uses the `librdkafka` C library.
*   **GLib Integration:** Utilises `GLib` for error handling and logging.

## Prerequisites

Before building and running this project, ensure you have the following installed:

*   `gcc`
*   `make`
*   `librdkafka`
*   `GLib`

## Building the Project

To compile the producer and consumer applications, navigate to the `src/` directory and run `make`:

```bash
make
```

This will create two executables: `producer` and `consumer`.

## Running the Applications

### 1. Run the Kafka Consumer

First, start the consumer to listen for messages:

```bash
./consumer
```

The consumer will connect to the `sample_data_stock_trades` topic and print any consumed messages to the console. It will continuously wait for messages.

### 2. Run the Kafka Producer

In a separate terminal, run the producer to send synthetic stock trade events:

```bash
./producer
```

The producer will generate 10 random stock trade messages and send them to the `sample_data_stock_trades` topic. After sending the messages, the producer will exit.

You should see the messages appear in the consumer's terminal.
