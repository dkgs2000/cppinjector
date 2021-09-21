﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Pipes;
using Client.Brain;

namespace Client
{
    class BrainMessanger
    {
        private readonly NamedPipeClientStream client;
        private readonly BinaryReader reader;
        private readonly BinaryWriter writer;

        public BrainMessanger()
        {
            client = new NamedPipeClientStream("BrainPipe");
            client.Connect();
            reader = new BinaryReader(client);
            writer = new BinaryWriter(client);
        }

        public BrainAnswer Request(BrainRequest request)
        {
            byte[] request_buffer = new byte[BrainRequest.request_buffer_size];
            BitConverter.GetBytes(request.function).CopyTo(request_buffer, 0);

            request.parametersBuffer.CopyTo(request_buffer, sizeof(int));

            writer.Write(request_buffer);
            writer.Flush();
            BrainAnswer answer = new BrainAnswer(reader.ReadBytes(sizeof(int)));
            return answer;
        }
    }
}
