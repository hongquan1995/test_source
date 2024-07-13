  osMessageQDef(qSIM_SIM_Update, 10, 4);
  qSIM_SIM_UpdateHandle = osMessageCreate(osMessageQ(qSIM_SIM_Update), NULL);