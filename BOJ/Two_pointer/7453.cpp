void twoPointer()
{
	ll AB_size{ AB_Partial.size() - 1 };
	ll CD_size{ CD_Partial.size() - 1 };

	ll left{ 0 };
	ll right{ CD_Partial.size() - 1 };

	while (left <= AB_size && right >= 0)
	{
		auto sum{ AB_Partial[left] + CD_Partial[right] };

		if (sum > 0)
			--right;
		else if (sum < 0)
			++left;
		else
		{
			ll tempLeft{ left };
			ll tempRight{ right };
			ll leftCnt{ 0 };
			ll rightCnt{ 0 };

			while (tempLeft <= AB_size && AB_Partial[tempLeft] + CD_Partial[right] == 0)
			{
				++tempLeft;
				++leftCnt;
			}

			while (tempRight <= CD_size && AB_Partial[left] + CD_Partial[tempRight] == 0)
			{
				--tempRight;
				++rightCnt;
			}

			result += leftCnt * rightCnt;

			left = tempLeft;
			right = tempRight;
		}
	}
}