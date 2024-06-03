import '@/styles/tailwind.css'

import clsx from 'clsx'
import localFont from 'next/font/local'
import { Inter } from 'next/font/google'
import { Layout } from '@/components/Layout'
import { Providers } from '@/app/providers'

const inter = Inter({
  subsets: ['latin'],
  display: 'swap',
  variable: '--font-inter',
})

// Use local version of Lexend so that we can use OpenType features
const lexend = localFont({
  src: '../fonts/lexend.woff2',
  display: 'swap',
  variable: '--font-lexend',
})

export const metadata = {
  title: {
    template: '%s - NetWizard Docs',
    default: 'NetWizard Docs - No need to hard-code WiFi credentials ever again.',
  },
  description: 'An easy-to-use yet powerful WiFi manager and captive portal library for wireless microcontrollers',
}

export default function RootLayout({ children }) {
  return (
    <html
      lang="en"
      className={clsx('h-full antialiased scroll-smooth', inter.variable, lexend.variable)}
      suppressHydrationWarning
    >
      <body className="flex min-h-full bg-white dark:bg-gray-900">
        <Providers>
          <Layout>{children}</Layout>
        </Providers>
      </body>
    </html>
  )
}
