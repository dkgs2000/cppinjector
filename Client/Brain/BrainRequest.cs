using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Brain
{
    class BrainRequest
    {
        private BrainFunctions Function { get; }
        private byte[] ParametersBuffer { get; }
        private static readonly int brain_request_message_size = 1024;

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

        public byte[] GetBrainRequestBuffer()
        {
            byte[] brain_request_buffer = new byte[BrainRequest.brain_request_message_size];
            BitConverter.GetBytes((int)this.Function).CopyTo(brain_request_buffer, 0);
            this.ParametersBuffer.CopyTo(brain_request_buffer, sizeof(BrainFunctions));

            return brain_request_buffer;
        }
    }
}
