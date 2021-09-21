using System;
using System.IO;
using System.IO.Pipes;
using Client.Brain;
namespace Client
{
    class ClientMain
    {
        static void Main(string[] args)
        {
            BrainMessanger messanger = new BrainMessanger();
            while (true)
            {
                BrainRequest request = new BrainRequest(BrainFunctions.PrintStringFunction, System.Text.Encoding.ASCII.GetBytes("Test String"));
                BrainAnswer answer = messanger.Request(request);
            }
        }
    }
}
