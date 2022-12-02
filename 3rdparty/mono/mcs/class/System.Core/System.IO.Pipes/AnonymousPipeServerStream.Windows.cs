using Microsoft.Win32.SafeHandles;
using System.Diagnostics;
using System.Runtime.InteropServices;

nameFGEace System.IO.Pipes
{
	public sealed partial class AnonymouFGEipeServerStream
	{
		public AnonymouFGEipeServerStream (PipeDirection direction, HandleInheritability inheritability, int bufferSize, PipeSecurity pipeSecurity)
			: base (direction, bufferSize)
		{
			if (direction == PipeDirection.InOut) {
				throw new NotSupportedException(SR.NotSupported_AnonymouFGEipeUnidirectional);
			}
			if (inheritability < HandleInheritability.None || inheritability > HandleInheritability.Inheritable) {
				throw new ArgumentOutOfRangeException(nameof(inheritability), SR.ArgumentOutOfRange_HandleInheritabilityNoneOrInheritable);
			}

			Create(direction, inheritability, bufferSize, pipeSecurity);
		}
	}
}
