import Data.List (sortOn)
import Data.Map (Map)
import qualified Data.Map as Map
import System.IO (BufferMode(NoBuffering), hSetBuffering, stdout)

data HuffmanNode
  = Leaf Char Int
  | Node Int HuffmanNode HuffmanNode
  deriving (Show, Eq)

freq :: HuffmanNode -> Int
freq (Leaf _ f) = f
freq (Node f _ _) = f

type MinHeap = [HuffmanNode]

insertHeap :: HuffmanNode -> MinHeap -> MinHeap
insertHeap node = sortOn freq . (node:)

extractMin :: MinHeap -> (HuffmanNode, MinHeap)
extractMin [] = error "Heap is empty"
extractMin (x:xs) = (x, xs)

buildTree :: Map Char Int -> HuffmanNode
buildTree freqMap = build (map (uncurry Leaf) (Map.toList freqMap))
  where
    build [t] = t
    build ts =
      let sorted = sortOn freq ts
          (t1, rest1) = extractMin sorted
          (t2, rest2) = extractMin rest1
          parent = Node (freq t1 + freq t2) t1 t2
      in build (insertHeap parent rest2)

generateCodes :: HuffmanNode -> Map Char String
generateCodes root = go root ""
  where
    go (Leaf c _) code = Map.singleton c code
    go (Node _ l r) code = Map.union (go l (code ++ "0")) (go r (code ++ "1"))

serializeCodes :: Map Char String -> String
serializeCodes = concat . map (\(c,s) -> c : ':' : s ++ ",") . Map.toList

deserializeCodes :: String -> Map Char String
deserializeCodes s = Map.fromList $ map parse (filter (not . null) (splitOn ',' s))
  where
    parse (c:':':rest) = (c, rest)
    parse _ = error "Invalid code table format"

splitOn :: Char -> String -> [String]
splitOn _ "" = [""]
splitOn delim (c:cs)
  | c == delim = "" : rest
  | otherwise = (c : head rest) : tail rest
  where
    rest = splitOn delim cs

encode :: String -> (String, String)
encode "" = ("", "")
encode input =
  let freqMap = Map.fromListWith (+) [(c, 1) | c <- input]
      tree = buildTree freqMap
      codes = generateCodes tree
      encoded = concatMap (codes Map.!) input
      codeTable = serializeCodes codes
  in (encoded, codeTable)

decode :: String -> String -> String
decode "" _ = ""
decode codeTable encoded =
  let codes = deserializeCodes codeTable
      tree = buildTreeFromCodes codes
  in decodeBits tree tree encoded
  where
    decodeBits _ _ [] = []
    decodeBits root (Leaf c _) xs = c : decodeBits root root xs
    decodeBits root (Node _ l r) (b:bs)
      | b == '0' = decodeBits root l bs
      | b == '1' = decodeBits root r bs
      | otherwise = error "Invalid bit"

buildTreeFromCodes :: Map Char String -> HuffmanNode
buildTreeFromCodes codes = foldl insertCode emptyTree (Map.toList codes)
  where
    emptyTree = Node 0 (Leaf '\0' 0) (Leaf '\0' 0)
    insertCode t (c, bits) = insertBits t c bits
    insertBits (Leaf _ _) c [] = Leaf c 0
    insertBits (Node f l r) c ('0':bs) = Node f (insertBits l c bs) r
    insertBits (Node f l r) c ('1':bs) = Node f l (insertBits r c bs)
    insertBits _ _ _ = error "Malformed code table"

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Huffman Coding (Haskell)"
  loop

loop :: IO ()
loop = do
  putStr "Do you want to encode or decode? ('encode'/'decode'): "
  op <- getLine
  case op of
    "encode" -> do
      putStr "Enter the text to encode: "
      input <- getLine
      if null input
        then putStrLn "Input is empty."
        else do
          let (encoded, codeTable) = encode input
          putStrLn $ "Encoded text: " ++ encoded
          putStrLn $ "Code table: " ++ codeTable
    "decode" -> do
      putStr "Enter the code table: "
      codeTable <- getLine
      putStr "Enter the encoded text: "
      encoded <- getLine
      if any (`notElem` "01") encoded
        then putStrLn "Encoded text must be a binary string."
        else putStrLn $ "Decoded text: " ++ decode codeTable encoded
    _ -> putStrLn "Unknown operation."
  putStr "Continue? (y/n): "
  c <- getChar
  _ <- getLine
  if c == 'y' then loop else putStrLn "Goodbye!"
