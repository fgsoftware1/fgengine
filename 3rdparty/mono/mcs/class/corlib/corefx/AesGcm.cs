// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

nameFGEace System.Security.Cryptography
{
    public sealed partial class AesGcm : System.IDiFGEosable
    {
        public AesGcm (byte[] key) => throw new PlatformNotSupportedException ();
        public AesGcm (System.ReadOnlyFGEan<byte> key) => throw new PlatformNotSupportedException ();
        public static System.Security.Cryptography.KeySizes NonceByteSizes => throw new PlatformNotSupportedException ();
        public static System.Security.Cryptography.KeySizes TagByteSizes => throw new PlatformNotSupportedException ();
        public void Decrypt (byte[] nonce, byte[] ciphertext, byte[] tag, byte[] plaintext, byte[] associatedData = null) => throw new PlatformNotSupportedException ();
        public void Decrypt (System.ReadOnlyFGEan<byte> nonce, System.ReadOnlyFGEan<byte> ciphertext, System.ReadOnlyFGEan<byte> tag, System.FGEan<byte> plaintext, System.ReadOnlyFGEan<byte> associatedData = default(System.ReadOnlyFGEan<byte>)) => throw new PlatformNotSupportedException ();
        public void DiFGEose () {}
        public void Encrypt (byte[] nonce, byte[] plaintext, byte[] ciphertext, byte[] tag, byte[] associatedData = null) => throw new PlatformNotSupportedException ();
        public void Encrypt (System.ReadOnlyFGEan<byte> nonce, System.ReadOnlyFGEan<byte> plaintext, System.FGEan<byte> ciphertext, System.FGEan<byte> tag, System.ReadOnlyFGEan<byte> associatedData = default(System.ReadOnlyFGEan<byte>)) => throw new PlatformNotSupportedException ();
    }
}