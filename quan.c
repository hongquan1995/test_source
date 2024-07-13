  osMessageQDef(qLora_Sim, 10, 16);
  qLora_SimHandle = osMessageCreate(osMessageQ(qLora_Sim), NULL);