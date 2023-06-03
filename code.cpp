# Solitaire-code
using System;
using System.Collections.Generic;

class KlondikeSolitaire
{
    private const int NumPiles = 7;
    private const int NumSuits = 4;
    private const int NumRanks = 13;

    private List<Card>[] piles = new List<Card>[NumPiles];
    private List<Card>[] foundation = new List<Card>[NumSuits];
    private List<Card> stock = new List<Card>();
    private List<Card> waste = new List<Card>();

    private Random random = new Random();

    private enum CardSuit { Spades, Hearts, Diamonds, Clubs };
    private enum CardRank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

    private class Card
    {
        public CardSuit Suit { get; set; }
        public CardRank Rank { get; set; }
        public bool IsFaceUp { get; set; }

        public Card(CardSuit suit, CardRank rank, bool isFaceUp = false)
        {
            Suit = suit;
            Rank = rank;
            IsFaceUp = isFaceUp;
        }
    }

    public void Initialize()
    {
        Console.Title = "Klondike Solitaire";
        Console.CursorVisible = false;

        InitializePiles();
        InitializeFoundation();
        InitializeStock();
        ShuffleStock();
        DealCards();

        Console.WriteLine("Welcome to Klondike Solitaire!");
        Console.WriteLine("Instructions:");
        Console.WriteLine(" - Use arrow keys to move the cursor.");
        Console.WriteLine(" - Press 'Enter' to select a card or move it.");
        Console.WriteLine(" - Press 'Q' to quit the game.");

        Console.WriteLine();
        Console.WriteLine("Good luck!");
        Console.WriteLine();
    }

    private void InitializePiles()
    {
        for (int i = 0; i < NumPiles; i++)
        {
            piles[i] = new List<Card>();
        }
    }

    private void InitializeFoundation()
    {
        for (int i = 0; i < NumSuits; i++)
        {
            foundation[i] = new List<Card>();
        }
    }

    private void InitializeStock()
    {
        for (int suit = 0; suit < NumSuits; suit++)
        {
            for (int rank = 1; rank <= NumRanks; rank++)
            {
                Card card = new Card((CardSuit)suit, (CardRank)rank);
                stock.Add(card);
            }
        }
    }

    private void ShuffleStock()
    {
        int n = stock.Count;
        while (n > 1)
        {
            n--;
            int k = random.Next(n + 1);
            Card temp = stock[k];
            stock[k] = stock[n];
            stock[n] = temp;
        }
    }

    private void DealCards()
    {
        int cardsToDeal = 1;

        for (int i = 0; i < NumPiles; i++)
        {
            for (int j = 0; j < cardsToDeal; j++)
            {
                Card card = stock[0];
                stock.RemoveAt(0);
                piles[i].Add(card);
            }
            cardsToDeal++;
        }

        stock.Reverse();
    }

    public void Play()
    {
        int cursorX = 0;
        int cursorY = 0;

        while (true)
        {
            Console.Clear();
            DrawBoard(cursorX, cursorY);

            Console
