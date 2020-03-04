module Lexer where

import Data.List
import Data.Char

data Token = Sym Char
	   | Or
	   | Star
	   | Plus
	   | Mb
    deriving (Show, Eq)

scan :: String -> [Token]
scan = unfoldr matchToken

matchToken :: String -> Maybe (Token, String)
matchToken ('|' : xs) = Just (Or   , xs)
matchToken ('*' : xs) = Just (Star , xs)
matchToken ('+' : xs) = Just (Plus , xs)
matchToken ('?' : xs) = Just (Mb   , xs)
matchToken (x   : xs) = Just (Sym x, xs)
matchToken []         = Nothing
