// #include <Arduino.h>
// #include <WiFi.h>
// #include <ezTime.h>

// Timezone sp;

// void conexaoWifi();
// void reConexaoWifi();

// const char *SSID = "SENAI EDUCACIONAL";
// const char *SENHA = "info@134";

// const unsigned long tempoConexao = 10000;
// const unsigned long tempoReConexao = 5000;

// String diaSemanaBR() {
//   const char* dias[] = {
//       "Domingo", "Segunda-feira", "Terca-feira",
//       "Quarta-feira", "Quinta-feira", "Sexta-feira",
//       "Sabado"
//   };

//   return dias[sp.weekday() - 1];
// }

// String mesBR() {
//   const char* meses[] = {
//       "Janeiro", "Fevereiro", "Marco", "Abril",
//       "Maio", "Junho", "Julho", "Agosto",
//       "Setembro", "Outubro", "Novembro", "Dezembro"
//   };

//   return meses[sp.month() - 1];
// }

// int diasRestantesAno() {

//   int ano = sp.year();

//   int totalDias = 365;

//   // Verifica se o ano é bissexto
//   if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
//       totalDias = 366;
//   }

//   return totalDias - sp.dayOfYear();
// }


// void setup() {
//   Serial.begin(115200);
  
//   conexaoWifi();
  
//   waitForSync();

//   sp.setLocation("America/Sao_Paulo");


//   // Serial.println(sp.dateTime());
//   // Serial.println(sp.dateTime("d/m/Y H:i:s"));
//   Serial.printf("Hoje e %s de %s de %i, %s e faltam %i para o ano novo. \n", diaSemanaBR().c_str, mesBR().c_str,  sp.dateTime("Y").c_str, diasRestantesAno());
  
// }

// void loop() {
//   reConexaoWifi();
// }




// void conexaoWifi()
// {
//   Serial.printf(" Conectando ao Wifi: %s", SSID);

//   WiFi.begin(SSID, SENHA);

//   unsigned long tempoWifi = millis();

//   while (WiFi.status() !=WL_CONNECTED && millis() - tempoWifi < tempoConexao)
//   {
//     Serial.print(".");
//     delay(500);
//   }

//   if (WiFi.status() == WL_CONNECTED)
//   {
//     Serial.println("Wifi conectado com sucesso!");
//     Serial.print("Endereco IP: ");
//     Serial.println(WiFi.localIP());
//   }
//   else
//   {
//     Serial.println("Falha ao se conectar");
//   }
// }

// void reConexaoWifi()
// {
//   static unsigned long tempoUltimaConexao = 0;
//   unsigned long tempoAtual = millis();

//   if (tempoAtual - tempoUltimaConexao > tempoReConexao)
//   {
//     if (WiFi.status() != WL_CONNECTED)
//     {
//       Serial.println("Conexao Wifi perdida");
//       conexaoWifi();
//     }
//     tempoUltimaConexao = tempoAtual;
//   }
  
// }



#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>

void conexaoWifi();
void reConexaoWifi();

String diaSemanaBR();
String mesBR();
int diasRestantesAno();

const char *SSID = "SENAI EDUCACIONAL";
const char *SENHA = "info@134";

const unsigned long tempoConexao = 10000;
const unsigned long tempoReConexao = 5000;

Timezone sp;

void setup() {
  Serial.begin(115200);

  conexaoWifi();

  if (WiFi.status() == WL_CONNECTED) {
    sp.setLocation("America/Sao_Paulo");

    waitForSync();

    Serial.printf(
      "Hoje e %s de %s de %s, %s e faltam %i dias para o ano novo.\n",
      String(sp.day()).c_str(),
      mesBR().c_str(),
      sp.dateTime("Y").c_str(),
      diaSemanaBR().c_str(),
      diasRestantesAno()
    );
  }
}

void loop() {
  reConexaoWifi();
}

String diaSemanaBR() {
  const char* dias[] = {
    "Domingo", "Segunda-feira", "Terca-feira",
    "Quarta-feira", "Quinta-feira", "Sexta-feira",
    "Sabado"
  };

  return dias[sp.weekday() - 1];
}

String mesBR() {
  const char* meses[] = {
    "Janeiro", "Fevereiro", "Marco", "Abril",
    "Maio", "Junho", "Julho", "Agosto",
    "Setembro", "Outubro", "Novembro", "Dezembro"
  };

  return meses[sp.month() - 1];
}

int diasRestantesAno() {
  int ano = sp.year();

  int totalDias = 365;

  if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
    totalDias = 366;
  }

  return totalDias - sp.dayOfYear();
}

void conexaoWifi() {
  Serial.printf("Conectando ao Wi-Fi: %s\n", SSID);

  WiFi.begin(SSID, SENHA);

  unsigned long tempoWifi = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - tempoWifi < tempoConexao) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi conectado com sucesso!");
    Serial.print("Endereco IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao se conectar.");
  }
}

void reConexaoWifi() {
  static unsigned long tempoUltimaConexao = 0;

  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoUltimaConexao >= tempoReConexao) {

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Conexao Wi-Fi perdida!");
      conexaoWifi();
    }

    tempoUltimaConexao = millis();
  }
}