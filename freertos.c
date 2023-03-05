/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of sem_FTP_Data */
  osSemaphoreDef(sem_FTP_Data);
  sem_FTP_DataHandle = osSemaphoreCreate(osSemaphore(sem_FTP_Data), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of qLora_Sim */
  osMessageQDef(qLora_Sim, 10, 16);
  qLora_SimHandle = osMessageCreate(osMessageQ(qLora_Sim), NULL);

  /* definition and creation of qSIM_SIM_Update */
  osMessageQDef(qSIM_SIM_Update, 10, 4);
  qSIM_SIM_UpdateHandle = osMessageCreate(osMessageQ(qSIM_SIM_Update), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of TaskFTP */
  osThreadDef(TaskFTP, Task_Control_FTP, osPriorityHigh, 0, 512);
  TaskFTPHandle = osThreadCreate(osThread(TaskFTP), NULL);

  /* definition and creation of TaskControlSim */
  osThreadDef(TaskControlSim, Task_Control_Sim, osPriorityNormal, 0, 512);
  TaskControlSimHandle = osThreadCreate(osThread(TaskControlSim), NULL);

  /* definition and creation of TaskUartSim */
  osThreadDef(TaskUartSim, Task_Uart_Sim, osPriorityNormal, 0, 256);
  TaskUartSimHandle = osThreadCreate(osThread(TaskUartSim), NULL);

  /* definition and creation of LoRaProcessTask */
  osThreadDef(LoRaProcessTask, StartLoRaProcessTask, osPriorityNormal, 0, 256);
  LoRaProcessTaskHandle = osThreadCreate(osThread(LoRaProcessTask), NULL);

  /* definition and creation of LoRaResponseTas */
  osThreadDef(LoRaResponseTas, StartLoRaResponseTask, osPriorityNormal, 0, 256);
  LoRaResponseTasHandle = osThreadCreate(osThread(LoRaResponseTas), NULL);

  /* definition and creation of motorTask */
  osThreadDef(motorTask, StartControlMotor, osPriorityBelowNormal, 0, 256);
  motorTaskHandle = osThreadCreate(osThread(motorTask), NULL);

  /* definition and creation of con1Task */
  osThreadDef(con1Task, StartCon1Task, osPriorityBelowNormal, 0, 128);
  con1TaskHandle = osThreadCreate(osThread(con1Task), NULL);

  /* definition and creation of con2Task */
  osThreadDef(con2Task, StartCon2Task, osPriorityBelowNormal, 0, 128);
  con2TaskHandle = osThreadCreate(osThread(con2Task), NULL);

  /* definition and creation of con3Task */
  osThreadDef(con3Task, StartCon3Task, osPriorityBelowNormal, 0, 128);
  con3TaskHandle = osThreadCreate(osThread(con3Task), NULL);

  /* definition and creation of con4Task */
  osThreadDef(con4Task, StartCon4Task, osPriorityBelowNormal, 0, 128);
  con4TaskHandle = osThreadCreate(osThread(con4Task), NULL);

  /* definition and creation of ComunicationTas */
  osThreadDef(ComunicationTas, Comunication_Task, osPriorityBelowNormal, 0, 256);
  ComunicationTasHandle = osThreadCreate(osThread(ComunicationTas), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Task_Control_FTP */
/**
  * @brief  Function implementing the TaskFTP thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Task_Control_FTP */
void Task_Control_FTP(void const * argument)
{

  /* USER CODE BEGIN Task_Control_FTP */
    osSemaphoreWait(sem_FTP_DataHandle,100);
    Set_default_FTP();
    sFTP.Receiver_u8 		= NONE;
    sFTP.FirmWare_Length 	= 21680;
    /* Infinite loop */
    for(;;)
    {
        osDelay(5);
		WATCH_DOG;
    }
  /* USER CODE END Task_Control_FTP */
}

/* USER CODE BEGIN Header_Task_Control_Sim */
/**
* @brief Function implementing the TaskControlSim thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Control_Sim */
void Task_Control_Sim(void const * argument)
{
  /* USER CODE BEGIN Task_Control_Sim */
    GLCD_Initialize();
    GLCD_ClearScreen();
    osDelay(1000);
    Get_RTC();
    GLCD_Display_RTC(1,18,sRTC);
    GLCD_WriteString("      XIN CHAO!     ",3,0,FONT5x7);
    osDelay(2000);
    GLCD_ClearScreen();
    //
    ON_BUZZER;
    GLCD_WriteString(" Nhan ENT de bat dau",4,0,FONT5x7);
    Wait_ButtonPress(BUTTON_ENT);
      /* Infinite loop */
    for(;;)
    {
        osDelay(5);
        Get_RTC();
        sButton.Value_u8 = 0;
        switch(Step_test_u8)
        {
            case 0: // Check phim bam
                  GLCD_ClearScreen();
                  GLCD_WriteString("  Kiem tra phim bam  ",1,0,FONT5x7);
                  GLCD_WriteString("     -> Nhan ESC     ",3,0,FONT5x7);
                  // Select Esc
                  Wait_ButtonPress(BUTTON_ESC);
                  // Select Ent
                  GLCD_WriteString("     -> Nhan ENT     ",3,0,FONT5x7);
                  Wait_ButtonPress(BUTTON_ENT);
                  // Select Up
                  GLCD_WriteString("     -> Nhan UP      ",3,0,FONT5x7);
                  Wait_ButtonPress(BUTTON_UP);
                  // Select Down
                  GLCD_WriteString("     -> Nhan DOWN   ",3,0,FONT5x7);
                  Wait_ButtonPress(BUTTON_DOWN);
                  Test_NextStep();
            break;
            case 1: // Check Led
                  GLCD_ClearScreen();
                  GLCD_WriteString("    Kiem tra LED    ",1,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_STATUS_PORT,LED_STATUS_PIN,LED_OFF);
                  HAL_GPIO_WritePin(LED_WAN1_PORT,LED_WAN1_PIN,LED_OFF);
                  HAL_GPIO_WritePin(LED_WAN2_PORT,LED_WAN2_PIN,LED_OFF);
                  HAL_GPIO_WritePin(LED_PHASEA_PORT,LED_PHASEA_PIN,LED_OFF);
                  HAL_GPIO_WritePin(LED_PHASEB_PORT,LED_PHASEB_PIN,LED_OFF);
                  HAL_GPIO_WritePin(LED_PHASEC_PORT,LED_PHASEC_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED STATUS: BAT  ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_STATUS_PORT,LED_STATUS_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED STATUS: TAT  ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_STATUS_PORT,LED_STATUS_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED WANR1: BAT   ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_WAN1_PORT,LED_WAN1_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED WANR1: TAT   ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_WAN1_PORT,LED_WAN1_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED WANR2: BAT   ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_WAN2_PORT,LED_WAN2_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED WANR2: TAT   ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_WAN2_PORT,LED_WAN2_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE A: BAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEA_PORT,LED_PHASEA_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE A: TAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEA_PORT,LED_PHASEA_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE B: BAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEB_PORT,LED_PHASEB_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE B: TAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEB_PORT,LED_PHASEB_PIN,LED_OFF);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE C: BAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEC_PORT,LED_PHASEC_PIN,LED_ON);
                  osDelay(1000);
                  GLCD_WriteString("   LED PHASE C: TAT ",3,0,FONT5x7);
                  HAL_GPIO_WritePin(LED_PHASEC_PORT,LED_PHASEC_PIN,LED_OFF);
                  osDelay(1000);
                  Test_NextStep();
            break;
            case 2: // Check EEPROM
                  GLCD_ClearScreen();
                  GLCD_WriteString("  Kiem tra EEPROM    ",1,0,FONT5x7);
                  osDelay(2000);
                  TestEEPROM();
                  if(sFROM_Manager.status_u8 == 1)
                  {
                      GLCD_WriteString("      EEPROM Loi     ",3,0,FONT5x7);
                      Wait_ButtonPress(BUTTON_ESC);
                        Step_test_u8 = 0;
                  }
                  else
                  {
                      GLCD_WriteString("      EEPROM OK      ",3,0,FONT5x7);
                      osDelay(2000);
                      Test_NextStep();
                  }
              break;
            case 3: // Check Module SIM
                 GLCD_ClearScreen();
                 GLCD_WriteString("      Kiem tra SIM   ",1,0,FONT5x7);
                 if(Hard_Reset() == TRUE){
                     GLCD_WriteString("         SIM OK      ",3,0,FONT5x7);
                     osDelay(2000);
                     Test_NextStep();
                 }
                 else{
                     GLCD_WriteString("        SIM ERR      ",3,0,FONT5x7);
                     Wait_ButtonPress(BUTTON_ESC);
                     Step_test_u8 = 0;
                 }
              break;
            case 4: // Check khoi do
                    GLCD_ClearScreen();
                    GLCD_WriteString("   Kiem tra khoi do  ",0,0,FONT5x7);
                    osDelay(2000);
                    // Khoi do 1
                    // Hien thi ket qua do
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSVol_PA_x100/10,1,2,0);
                    GLCD_WriteCharacter('V',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSVol_PB_x100/10,1,2,45);
                    GLCD_WriteCharacter('V',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSVol_PC_x100/10,1,2,90);
                    GLCD_WriteCharacter('V',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSCur_PA_x100/10,1,3,0);
                    GLCD_WriteCharacter('A',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSCur_PB_x100/10,1,3,45);
                    GLCD_WriteCharacter('A',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data.RMSCur_PC_x100/10,1,3,90);
                    GLCD_WriteCharacter('A',FONT5x7);
                    // Khoi do 2 - ktra giao tiep SPI
                    GLCD_Write_Float_Not_Zero(Metering_Data_Alert.RMSCur_PA_x100/10,1,4,0);
                    GLCD_WriteCharacter('A',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data_Alert.RMSCur_PB_x100/10,1,4,45);
                    GLCD_WriteCharacter('A',FONT5x7);
                    GLCD_Write_Float_Not_Zero(Metering_Data_Alert.RMSCur_PC_x100/10,1,4,90);
                    GLCD_WriteCharacter('A',FONT5x7);
                    
                    if((Metering_Data.RMSVol_PA_x100/100 > 300)||(Metering_Data.RMSVol_PB_x100/100 > 300)||(Metering_Data.RMSVol_PC_x100/100 > 300)||\
                       (Metering_Data.RMSVol_PA_x100/100 < 200)||(Metering_Data.RMSVol_PB_x100/100 < 200)||(Metering_Data.RMSVol_PC_x100/100 < 200)||\
                       (Metering_Data.RMSCur_PA_x100/100 > 10)||(Metering_Data.RMSCur_PB_x100/100 > 10)||(Metering_Data.RMSCur_PC_x100/100 > 10)||\
                       (Metering_Data_Alert.RMSCur_PA_x100/100 > 10)||(Metering_Data_Alert.RMSCur_PB_x100/100 > 10)||(Metering_Data_Alert.RMSCur_PC_x100/100 > 10))
                    {
                        GLCD_WriteString("     Loi Khoi do!    ",5,0,FONT5x7);
                        Exit_PressESC_ENT();
                        Step_test_u8 = 0;
                    }
                    else
                    {
                        GLCD_WriteString("      Hoan Thanh!    ",5,0,FONT5x7);
                        GLCD_WriteString(" Nhan ENT de tiep tuc",6,0,FONT5x7);
                        Exit_PressESC_ENT();
                    }
              break;
            case 5: // Check 485
                    GLCD_ClearScreen();
                    GLCD_WriteString("     Kiem tra 485    ",1,0, FONT5x7);
                    GLCD_WriteString("   Gui \"TEST 485\"  ",1,0, FONT5x7);
                    Rs485SendData((uint8_t*)"Gui chuoi \"TEST 485\"", 20);
                    while(sRs485Manage.FB_Xifon_u8 != RS_TEST)
                    {
                        sButton.Value_u8 = 0;
                        sButton.Status_u8 = 0;
                        osDelay(10);
                        if(sButton.Value_u8 == BUTTON_ESC){ Step_test_u8++;  
                          break;}
                    }
                    if(sRs485Manage.FB_Xifon_u8 == RS_TEST)
                      Test_NextStep();
                    sRs485Manage.FB_Xifon_u8 = RS_TEMP;
              break;
            case 6:  // Switch
                      GLCD_ClearScreen();
                      GLCD_WriteString("   Kiem tra che do  ",1,0,FONT5x7);
                      GLCD_WriteString("   -> Che do OFF    ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if((Motor_Controller.controlMode_u8 != 1)&&(Motor_Controller.controlMode_u8 != 2))
                              break;
                            osDelay(10);
                      }
                      GLCD_WriteString("   -> Che do MAN    ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if(Motor_Controller.controlMode_u8 == 2)
                              break;
                            osDelay(10);
                      }
                      GLCD_WriteString("   -> Che do AUTO   ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if(Motor_Controller.controlMode_u8 == 1)
                              break;
                            osDelay(10);
                      }
                      //
                      GLCD_WriteString("   -> Che do OFF    ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if((Motor_Controller.controlMode_u8 != 1)&&(Motor_Controller.controlMode_u8 != 2))
                              break;
                            osDelay(10);
                      }
                      GLCD_WriteString("   -> Che do MAN    ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if(Motor_Controller.controlMode_u8 == 2)
                              break;
                            osDelay(10);
                      }
                      GLCD_WriteString("   -> Che do AUTO   ",3,0,FONT5x7);
                      while(1)
                      {
                            Check_Auto_Manual_Mode();
                            if(Motor_Controller.controlMode_u8 == 1)
                              break;
                            osDelay(10);
                      }
                      //
                      Test_NextStep();
                  break;
            case 7: // Check Relay
                      GLCD_ClearScreen();
                      GLCD_WriteString("     Kiem tra KHOI   ",1,0,FONT5x7);
                      GLCD_WriteString("      KHOI Oxy DONG  ",3,0,FONT5x7);
                      Motor_Controller.Oxy.control = 1;
                      Contactor_Control(&Motor_Controller.Oxy);
                      Motor_Controller.Fan1.control = 0;
                      Contactor_Control(&Motor_Controller.Fan1);
                      Motor_Controller.Fan2.control = 0;
                      Contactor_Control(&Motor_Controller.Fan2);
                      Motor_Controller.Xifon.control = 0;
                      Contactor_Control(&Motor_Controller.Xifon);
                      Motor_Controller.Lamp.control = 0;
                      Contactor_Control(&Motor_Controller.Lamp);
                      if(Motor_Controller.Oxy.status == 1)
                      {
                            GLCD_WriteString("      KHOI Oxy OK    ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ENT);
                      }
                      else
                      {
                            GLCD_WriteString("      KHOI Oxy Loi   ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ESC);
                      }
                        
                      GLCD_WriteString("    KHOI Quat 1 DONG ",3,0,FONT5x7);
                      Motor_Controller.Oxy.control = 0;
                      Contactor_Control(&Motor_Controller.Oxy);
                      Motor_Controller.Fan1.control = 1;
                      Contactor_Control(&Motor_Controller.Fan1);
                      Motor_Controller.Fan2.control = 0;
                      Contactor_Control(&Motor_Controller.Fan2);
                      Motor_Controller.Xifon.control = 0;
                      Contactor_Control(&Motor_Controller.Xifon);
                      Motor_Controller.Lamp.control = 0;
                      Contactor_Control(&Motor_Controller.Lamp);
                      
                      if(Motor_Controller.Fan1.status == 1)
                      {
                            GLCD_WriteString("     KHOI Quat 1 OK  ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ENT);
                      }
                      else
                      {
                            GLCD_WriteString("     KHOI Quat 1 Loi ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ESC);
                      }
                      
                      GLCD_WriteString("    KHOI Quat 2 DONG ",3,0,FONT5x7);
                      
                      Motor_Controller.Oxy.control = 0;
                      Contactor_Control(&Motor_Controller.Oxy);
                      Motor_Controller.Fan1.control = 0;
                      Contactor_Control(&Motor_Controller.Fan1);
                      Motor_Controller.Fan2.control = 1;
                      Contactor_Control(&Motor_Controller.Fan2);
                      Motor_Controller.Xifon.control = 0;
                      Contactor_Control(&Motor_Controller.Xifon);
                      Motor_Controller.Lamp.control = 0;
                      Contactor_Control(&Motor_Controller.Lamp);
                      
                      if(Motor_Controller.Fan2.status == 1)
                      {
                            GLCD_WriteString("    KHOI Quat 2 OK   ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ENT);
                      }
                      else
                      {
                            GLCD_WriteString("    KHOI Quat 2 Loi  ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ESC);
                      }
                      
                      GLCD_WriteString("    KHOI Xifon DONG  ",3,0,FONT5x7);
                      
                      Motor_Controller.Oxy.control = 0;
                      Contactor_Control(&Motor_Controller.Oxy);
                      Motor_Controller.Fan1.control = 0;
                      Contactor_Control(&Motor_Controller.Fan1);
                      Motor_Controller.Fan2.control = 0;
                      Contactor_Control(&Motor_Controller.Fan2);
                      Motor_Controller.Xifon.control = 1;
                      Contactor_Control(&Motor_Controller.Xifon);
                      Motor_Controller.Lamp.control = 0;
                      Contactor_Control(&Motor_Controller.Lamp);
                       
                      if(Motor_Controller.Xifon.status == 1)
                      {
                            GLCD_WriteString("    KHOI  Xifon OK   ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ENT);
                      }
                      else
                      {
                            GLCD_WriteString("    KHOI Xifon Loi   ",3,0,FONT5x7);
                            Wait_ButtonPress(BUTTON_ESC);
                      }
                      
                      GLCD_WriteString("   Bat cong tac DEN  ",3,0,FONT5x7);
                      
                      
                      
                      Motor_Controller.Oxy.control = 0;
                      Contactor_Control(&Motor_Controller.Oxy);
                      Motor_Controller.Fan1.control = 0;
                      Contactor_Control(&Motor_Controller.Fan1);
                      Motor_Controller.Fan2.control = 0;
                      Contactor_Control(&Motor_Controller.Fan2);
                      Motor_Controller.Xifon.control = 0;
                      Contactor_Control(&Motor_Controller.Xifon);
                      Motor_Controller.Lamp.control = 1;
                      Contactor_Control(&Motor_Controller.Lamp);
                      
                      GLCD_WriteString("       KET THUC!     ",3,0,FONT5x7);
                      Wait_ButtonPress(BUTTON_ESC);
                      Step_test_u8 = 0;
                break;
                // kiem tra coi bao
            default:
            break;
        }
    }
  /* USER CODE END Task_Control_Sim */
}

/* USER CODE BEGIN Header_Task_Uart_Sim */
/**
* @brief Function implementing the TaskUartSim thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Uart_Sim */
void Task_Uart_Sim(void const * argument)
{
  /* USER CODE BEGIN Task_Uart_Sim */
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
        UartSimProcess();
  }
  /* USER CODE END Task_Uart_Sim */
}

/* USER CODE BEGIN Header_StartLoRaProcessTask */
/**
* @brief Function implementing the LoRaProcessTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLoRaProcessTask */
void StartLoRaProcessTask(void const * argument)
{
  /* USER CODE BEGIN StartLoRaProcessTask */
//  osDelay(5000); // Wait Init EEPROM
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
  }
  /* USER CODE END StartLoRaProcessTask */
}

/* USER CODE BEGIN Header_StartLoRaResponseTask */
/**
* @brief Function implementing the LoRaResponseTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLoRaResponseTask */
void StartLoRaResponseTask(void const * argument)
{
  /* USER CODE BEGIN StartLoRaResponseTask */
//  osDelay(5000); // Wait Init EEPROM
  /* Infinite loop */
  for(;;)
  {
      osDelay(5);
  }
  /* USER CODE END StartLoRaResponseTask */
}

/* USER CODE BEGIN Header_StartControlMotor */
/**
* @brief Function implementing the motorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlMotor */
void StartControlMotor(void const * argument)
{
  /* USER CODE BEGIN StartControlMotor */
  uint16_t countTimeOutUpdateBuff = 20;
  Init_ATM90();
  spi_index = 1;
  Init_ATM90();
  spi_index = 0;
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
        countTimeOutUpdateBuff++;
        if(countTimeOutUpdateBuff > 190)
        {
          Mettering_Update_Data();
          countTimeOutUpdateBuff = 0;
          spi_index++;
          if(spi_index > 1)
            spi_index = 0;
          Get_RTC();
        }
  }
  /* USER CODE END StartControlMotor */
}

/* USER CODE BEGIN Header_StartCon1Task */
/**
* @brief Function implementing the con1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCon1Task */
void StartCon1Task(void const * argument)
{
  /* USER CODE BEGIN StartCon1Task */
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
  }
  /* USER CODE END StartCon1Task */
}

/* USER CODE BEGIN Header_StartCon2Task */
/**
* @brief Function implementing the con2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCon2Task */
void StartCon2Task(void const * argument)
{
  /* USER CODE BEGIN StartCon2Task */
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
  }
  /* USER CODE END StartCon2Task */
}

/* USER CODE BEGIN Header_StartCon3Task */
/**
* @brief Function implementing the con3Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCon3Task */
void StartCon3Task(void const * argument)
{
  /* USER CODE BEGIN StartCon3Task */
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
  }
  /* USER CODE END StartCon3Task */
}

/* USER CODE BEGIN Header_StartCon4Task */
/**
* @brief Function implementing the con4Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCon4Task */
void StartCon4Task(void const * argument)
{
  /* USER CODE BEGIN StartCon4Task */
//  osDelay(1000); // ???
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
  }
  /* USER CODE END StartCon4Task */
}

/* USER CODE BEGIN Header_Comunication_Task */
/**
* @brief Function implementing the ComunicationTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Comunication_Task */
void Comunication_Task(void const * argument)
{
  /* USER CODE BEGIN Comunication_Task */
 sButton.Timeout_NextButton_u32 = 1;
  /* Infinite loop */
  for(;;)
  {
        osDelay(5);
        Button_Scan();
        UartRs485Process();
  }
  /* USER CODE END Comunication_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
