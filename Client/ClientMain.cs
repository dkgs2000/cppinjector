using System;
using System.IO;
using System.IO.Pipes;

namespace Client
{
    class ClientMain
    {
        static void Main(string[] args)
        {
            var client = new NamedPipeClientStream("BrainPipe");
            client.Connect();
            StreamReader reader = new StreamReader(client);
            StreamWriter writer = new StreamWriter(client);

            while (true)
            {
                string input = Console.ReadLine();
                if (String.IsNullOrEmpty(input)) break;
                writer.WriteLine(input);
                writer.Flush();
                Console.WriteLine(reader.ReadLine());
            }
        }
    }
}
