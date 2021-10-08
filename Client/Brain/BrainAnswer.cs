using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Brain
{
    class BrainAnswer
    {
        private readonly int Function_return_value;

        public BrainAnswer(int function_return_value)
        {
            this.Function_return_value = function_return_value;
        }

        public BrainAnswer(byte[] input_buffer)
        {
            this.Function_return_value = BitConverter.ToInt32(input_buffer, 0);
        }

        public int GetFunctionReturnValue()
        {
            return this.Function_return_value;
        }
    }
}
