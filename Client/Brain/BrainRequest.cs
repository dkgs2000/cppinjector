using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Brain
{
    class BrainRequest
    {
        public static readonly int request_buffer_size = 1024;
        public int function { get; }
        public byte[] parametersBuffer { get; }

        public BrainRequest(BrainFunctions function, byte[] parametersBuffer)
        {
            this.function = (int)function;
            this.parametersBuffer = (byte[])parametersBuffer.Clone();
        }

        public BrainRequest(byte[] input_buffer)
        {
            this.function = BitConverter.ToInt32(input_buffer, 0);
            input_buffer.CopyTo(this.parametersBuffer, sizeof(int));
        }
    }
}
