using System;
using Microsoft.SPOT;
using System.Threading;
using Microsoft.SPOT.Hardware;
using SecretLabs.NETMF.Hardware;
using SecretLabs.NETMF.Hardware.Netduino;
using NetQuadCopter.libraries;

namespace NetQuadCopter.j
{
    public class IMUManager
    {
        /* Declaración de parámetros */
        // PINS
        private const Cpu.Pin AccXPin   = Pins.GPIO_PIN_A4;
        private const Cpu.Pin AccYPin   = Pins.GPIO_PIN_A3;
        private const Cpu.Pin AccZPin   = Pins.GPIO_PIN_A2;

        // Puertos
        private AnalogInput AccXPort, AccYPort, AccZPort;

        // Voltages
        private const short Vref = 3300; //mV
        private const short VzeroXG = 1658; //mV (a ojo tras probar)
        private const short VzeroYG = 1612; //mV (a ojo tras probar)
        private const short VzeroZG = 1629; //mV (a ojo tras probar)
        private const short AccSensibility = 300; // mV/g
        private const byte T = 50; // Milisegundos entre mediciones

        private const double PIMedios = System.Math.PI / 2;

        /* Declaración de propiedades públicas */
        public float Roll = 0;  // Alabeo
        public float Pitch = 0; // Cabeceo o profundidad
        public float Yaw = 0;   // Dirección

        public float RollInAngles{
            get { return (float)ToAngles(Roll); }
        }
        public float PitchInAngles{
            get { return (float)ToAngles(Pitch); }
        }
        public float YawInAngles{
            get { return (float)ToAngles(Yaw); }
        }


        /* miembros privados */
        private double Rx = -1;
        private double Ry = -1;
        private double Rz = -1;

        private Timer loopTimer;

        /* Variables declaradas globalmente para evitar estar declarandolas continuamente*/
        private int AdcRx;
        private int AdcRy;
        private int AdcRz;

        private double RxAcc;
        private double RyAcc;
        private double RzAcc;

        private double abs;

        // Y estas para debug
        private DateTime dtDebug;
        double milisecons;

        public IMUManager()
        {
            // Inicializo los puertos
            AccXPort = new AnalogInput(AccXPin);
            AccYPort = new AnalogInput(AccYPin);
            AccZPort = new AnalogInput(AccZPin);

            // Inicializo el timer
            loopTimer = new Timer(new System.Threading.TimerCallback(loopTimerCallback), null, 0, T);
        }

        /// <summary>
        /// Devuelve una traza con valores de variables privadas. Usado para depurar
        /// </summary>
        /// <returns></returns>
        public string GetDebug()
        {
            return "Pitch: " + PitchInAngles + ", Roll: " + RollInAngles;// +", Yaw: " + ToAngles(Yaw);
            //return "Tiempo: " + milisecons;
        }


        /// <summary>
        /// Pasa un ángulo en radianes a grados
        /// </summary>
        /// <param name="radians">Ángulo en radianes</param>
        /// <returns>Ángulo en grados</returns>
        private double ToAngles(float radians)
        {
            return 180 * radians / System.Math.PI;
        }


        /// <summary>
        /// Delegado del timer que se encarga de recalcular la posición del cuatricoptero
        /// </summary>
        /// <param name="obj"></param>
        private void loopTimerCallback(object obj)
        {
            dtDebug = DateTime.Now;

            #region Cálculo del vector de posición con el acelerómetro

            // Leemos los nuevos valores del acelerómetro
            AdcRx = AccXPort.Read(); // 586;
            AdcRy = AccYPort.Read(); // 630;
            AdcRz = AccZPort.Read(); // 561;

            // y los pasamos a G's
            RxAcc = (AdcRx * Vref / 1023.0f - VzeroXG) / AccSensibility; // g
            RyAcc = -1.0 * (AdcRy * Vref / 1023.0f - VzeroYG) / AccSensibility;
            RzAcc = (AdcRz * Vref / 1023.0f - VzeroZG) / AccSensibility;
            
            // y por último lo normalizo
            abs = exMath.Sqrt(RxAcc * RxAcc + RyAcc * RyAcc + RzAcc * RzAcc);
            RxAcc = RxAcc / abs;
            RyAcc = RyAcc / abs;
            RzAcc = RzAcc / abs;

            #endregion

            #region Finalmente calculamos los valores finales convinando los dos vectores (Acc y Gyro)
            
            // Finalmente calculamos los valores
            Rx = RxAcc;
            Ry = RyAcc;
            Rz = RzAcc;

            // y normalizamos
            abs = exMath.Sqrt(Rx*Rx + Ry*Ry + Rz*Rz);
            Rx = Rx / abs;
            Ry = Ry / abs;
            Rz = Rz / abs;

            #endregion

            //Actualizar Ángulos de Vuelo actuales
            Pitch = (float)(exMath.Atan2(Rz, Rx));   //  en Radianes
            Roll = (float)(exMath.Atan2(Ry, Rz) - PIMedios);    //  en Radianes              
            Yaw = 0; // (float)(exMath.Atan2(Ry, Rx) - System.Math.PI);     //  en Radianes

            // Apunto lo que he tardado en calcular una iteracción del bucle
            milisecons = (DateTime.Now.Subtract(dtDebug)).Milliseconds;
        }
    }
}
