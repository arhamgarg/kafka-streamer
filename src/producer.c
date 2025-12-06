#include <glib-2.0/glib.h>
#include <librdkafka/rdkafka.h>

#include "common.c"

#define ARR_SIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

static void dr_msg_cb(rd_kafka_t *kafka_handle,
                      const rd_kafka_message_t *rkmessage, void *opaque) {
  if (rkmessage->err) {
    g_error("Message delivery failed: %s", rd_kafka_err2str(rkmessage->err));
  }
}

int main(int argc, char **argv) {
  rd_kafka_t *producer;
  rd_kafka_conf_t *conf;
  rd_kafka_resp_err_t err;
  char errstr[512];

  conf = rd_kafka_conf_new();

  set_config(conf, "bootstrap.servers",
             "pkc-619z3.us-east1.gcp.confluent.cloud:9092");
  set_config(conf, "sasl.username", "FKZ4XO5WBXCYJ3KL");
  set_config(
      conf, "sasl.password",
      "cfltFYtCrVq684k196hchFjPi111P4RvNxe9bAkWOvMYm8kyzuxcSchztE+9JJmQ");

  set_config(conf, "security.protocol", "SASL_SSL");
  set_config(conf, "sasl.mechanisms", "PLAIN");
  set_config(conf, "acks", "all");

  rd_kafka_conf_set_dr_msg_cb(conf, dr_msg_cb);

  producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));

  if (!producer) {
    g_error("Failed to create new producer: %s", errstr);
    return 1;
  }

  conf = NULL;

  int message_count = 10;
  const char *topic = "sample_data_stock_trades";
  const char *sides[] = {"Buy", "Sell"};
  const char *symbols[] = {"AAPL", "AMZN", "GOOG", "META",
                           "MSFT", "NVDA", "TSLA"};

  for (int i = 0; i < message_count; i++) {
    const char *side = sides[random() % ARR_SIZE(sides)];
    const char *symbol = symbols[random() % ARR_SIZE(symbols)];

    int quantity = (random() % 5000) + 1;
    int price = (random() % 500) + 10;

    char message[256];
    snprintf(message, sizeof(message), "%s %d %s @ %d", side, quantity, symbol,
             price);

    size_t message_len = strlen(message);

    err = rd_kafka_producev(producer, RD_KAFKA_V_TOPIC(topic),
                            RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                            RD_KAFKA_V_VALUE(message, message_len),
                            RD_KAFKA_V_OPAQUE(NULL), RD_KAFKA_V_END);

    if (err) {
      g_error("Failed to produce to topic %s: %s", topic,
              rd_kafka_err2str(err));
      return 1;
    } else {
      g_message("%s", message);
    }

    rd_kafka_poll(producer, 0);
  }

  g_message("Flushing final messages..");
  rd_kafka_flush(producer, 10 * 1000);

  if (rd_kafka_outq_len(producer) > 0) {
    g_error("%d message(s) were not delivered", rd_kafka_outq_len(producer));
  }

  g_message("%d trade events produced to topic \"%s\".", message_count, topic);

  rd_kafka_destroy(producer);

  return 0;
}
