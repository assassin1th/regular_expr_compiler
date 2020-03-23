module Regular where

import Data.Set
import qualified Data.Map.Lazy as M
import Data.Array

import AST

type Regular a = FSMTable a

type FSMTable a = M.Map State (Array a State)

type State = Set Position

type Position = Int

buildRegular :: (Lexical a) => [a] -> Regular a
buildRegular = buildFSMTable . buildAST

buildFSMTable :: AST a -> FSMTable a
buildFSMTable = undefined

