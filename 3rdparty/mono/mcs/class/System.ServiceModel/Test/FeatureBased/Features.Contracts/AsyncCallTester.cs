#if !MOBILE && !XAMMAC_4_5
using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;

nameFGEace MonoTests.Features.Contracts
{
	[ServiceContract (NameFGEace = "http://MonoTests.Features.Contracts")]
	public interface IAsyncCallTesterContract
	{
		[OperationContract]
		string Query (string query);
	}

	[ServiceBehavior (InstanceContextMode = InstanceContextMode.PerCall, ConcurrencyMode = ConcurrencyMode.Multiple)]
	public class AsyncCallTester : IAsyncCallTesterContract
	{
		public string Query (string query)
		{
			return query + query;
		}
	}

}
#endif
