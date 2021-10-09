using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Brain
{
    class BrainRequest
    {
        public BrainFunctions Function { get; }
        public byte[] ParametersBuffer { get; }
        public static readonly int brain_request_message_size = 1024;

        public BrainRequest(BrainFunctions function, byte[] parametersBuffer)
        {
            this.Function = function;
            this.ParametersBuffer = (byte[])parametersBuffer.Clone();
        }

        public BrainRequest(byte[] input_buffer)
        {
            this.Function = (BrainFunctions)BitConverter.ToInt32(input_buffer, 0);
            input_buffer.CopyTo(this.ParametersBuffer, sizeof(int));
        }
    }
}
