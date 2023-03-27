declare module '@stoneagebr/windows-credman' {
   export function getCredentials(targetname: string): { username: string; password: string; }
}