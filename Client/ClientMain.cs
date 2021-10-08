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
            if (args is null)
            {
                throw new ArgumentNullException(nameof(args));
            }

            BrainMessanger messanger = new BrainMessanger();
            while (true)
            {
                BrainRequest request = new BrainRequest(BrainFunctions.PrintStringFunction, System.Text.Encoding.Unicode.GetBytes("Test String"));
                BrainAnswer answer = messanger.SendRequest(request);
                Console.WriteLine(answer.GetFunctionReturnValue().ToString());
                Console.ReadLine();
            }
        }
    }
}
