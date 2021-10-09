using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Brain
{
    class BrainAnswer
    {
        private readonly int function_return_value;
        public static readonly int brain_answer_message_size = 4; //sizeof(int)

        public BrainAnswer(int function_return_value)
        {
            this.function_return_value = function_return_value;
        }

        public BrainAnswer(byte[] input_buffer)
        {
            this.function_return_value = BitConverter.ToInt32(input_buffer, 0);
        }
    }
}
