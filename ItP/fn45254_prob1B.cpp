#include "iostream"

int main()
{

    size_t input = 0;
    int mask = 1, count = 0, shifts = 0;

    bool prevBit = 0;

    std::cin >> input;

    if (input <= 999999999)
    {
        // Loop until we've checked all the bits in the input number.
        while (mask <= input)
        {
            //checks if the current bit is 1.
            if (input & mask)
            {
                //checks if the prev bit was also 1.
                if (prevBit)
                {
                    ++count;
                    //shift the bit in the mask by one in the left side.
                    mask = mask << 1;

                    //loop until we find a bit that is a 0 or until the mask is larger that the input number.
                    while (mask <= input && (input & mask))
                    {
                        //count how many 1's we've encountered.
                        ++count;

                        //shift the bits again so we don't stand in one place.
                        mask = mask << 1;
                    }

                    //shift the mask twice to the right because we needn't change the last consecutive 1.
                    mask = mask >> 2;

                    //we only need to change every second odd bit starting from the leftmost 1.
                    for (size_t b = 1; b <= count; b += 2)
                    {
                        //changes the 1 to a 0.
                        input = input & (~mask);

                        //shift the masks bit twice to the right to "follow" the loops indexes.
                        //only if it doesn't change the mask to 0.
                        if (mask >> 2)
                            mask = mask >> 2;
                    }

                    //adds the count to the total shifts we've made so far on our mask.
                    shifts += count;

                    //shift the mask back to it's previous state.
                    mask = mask << shifts;

                    //the next bit is a 0.
                    prevBit = 0;
                }

                else
                    prevBit = 1; //sets the prev bit to 1.

                //resets the consecutive bits counter.
                count = 0;
            }
            else
            {
                //checks if the prev bit was a 0.
                if (!prevBit)
                {
                    //increments the counter.
                    ++count;
                    //shift the bit in the mask by one in the left side.
                    mask = mask << 1;

                    //loop until we find a bit that is a 1 or until the mask is larger that the input number.
                    while (mask <= input && !(input & mask))
                    {
                        //count how many 0's we've encountered.
                        ++count;

                        //shift the bits again so we don't stand in one place.
                        mask = mask << 1;
                    }

                    //shift the mask twice to the right because we needn't change the last consecutive 1.
                    mask = mask >> 2;

                    //we only need to change every second odd bit starting from the leftmost 1.
                    for (size_t b = 1; b <= count; b += 2)
                    {
                        //sets the curr 0 bit to a 1.
                        input = input | mask;

                        //shift the masks bit twice to the right to "follow" the loops indexes.
                        //only if it doesn't change the mask to 0.
                        if ((mask >> 2))
                            mask = mask >> 2;
                    }

                    //adds the count to the total shifts we've made so far on our mask.
                    shifts += count;

                    //shifts back the mask to it's previous state.
                    mask = mask << shifts;

                    //the next bit we've encountered is a 1.
                    prevBit = 1;
                }
                else
                    prevBit = 0; //the previous bit is 0.

                //resets the counter.
                count = 0;
            }

            mask = mask << 1;
            //std::cout << "mask is: " << mask << std::endl;
        }

        std::cout << input << std::endl;
    }

    return 0;
}