#include <stdio.h>
#include <string.h>

int main()
{
	
	printf("matchresult : %d\n", simpleMatch("*", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*O", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*o", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*l*", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*L*", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*L*O", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*L*x", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*E*L*", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("*E*L*X", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("HE*", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("HE*O", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("HE*X", "HELLO"));
	printf("matchresult : %d\n", simpleMatch("HE*L*O", "HELLO"));
	return 0;
	
}

int simpleMatch(char *pattern, char *txId)
{
	printf("------------------------------------------------------------------\n");
	printf("function start input pattern = %s, txId = %s\n", pattern, txId);
	if(pattern != NULL && txId != NULL)
	{
		char *firstAsterisk = strchr(pattern, '*');
		
		if(firstAsterisk != NULL)
		{
			int firstAsteriskIdx = firstAsterisk - pattern;
			
			if(firstAsteriskIdx == 0)
			{
				if(strlen(pattern) == 1)
				{
					return 1;
				}
				firstAsterisk += 1;
				
				char *nextAsterisk = strchr(firstAsterisk, '*');
				
				if(nextAsterisk != NULL)
				{
					
					int nextAsteriskIdx = nextAsterisk - pattern;
					
					if(nextAsteriskIdx == 1)
					{
						return simpleMatch(nextAsterisk, txId);
					}
					char part[nextAsteriskIdx + 1];
					memset(part, '\0', nextAsteriskIdx + 1);
					strncpy(part, pattern + 1, nextAsteriskIdx - 1);
					char *partResult = strstr(txId, part);
					while(partResult != NULL)
					{
						char *txIdTail = partResult + strlen(part);
						if(simpleMatch(nextAsterisk, txIdTail) == 1)
						{
							return 1;
						}
						partResult = strstr(txIdTail, part);
					}
					return 0;
				}
				else
				{
					char *endWithResult = strstr(txId, firstAsterisk);

					if(endWithResult != NULL && strlen(endWithResult) == strlen(firstAsterisk))
					{
						return 1;
					}
					return 0;
				}
			}
			
			char substringPattern[firstAsteriskIdx + 1];
			char substringTxId[firstAsteriskIdx + 1];
			memset(substringPattern, '\0', firstAsteriskIdx + 1);
			memset(substringTxId, '\0', firstAsteriskIdx + 1);
			strncpy(substringPattern, pattern, firstAsteriskIdx);
			strncpy(substringTxId, txId, firstAsteriskIdx);
			
			return (strlen(txId) >= firstAsteriskIdx && strcmp(substringPattern, substringTxId) == 0 && simpleMatch(pattern + firstAsteriskIdx, txId + firstAsteriskIdx));
		}
		return strcmp(pattern, txId) == 0;
	}
	else
	{
		return -1;

	}
}
