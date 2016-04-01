using SCPSInventory.Models;
using System.Data.Entity;

namespace SCPSInventory.DAL
{
    public class SCPSInventoryContext : DbContext
    {
        public SCPSInventoryContext() : base("SCPSInventoryContext") { }
        public DbSet<CostCenter> CostCenters { get; set; }
        public DbSet<Asset> Assets { get; set; }
        public DbSet<Inventory> Inventories { get; set; }
    }
}