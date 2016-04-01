using System.Data;
using System.Linq;
using System.Net;
using System.Web.Mvc;
using SCPSInventory.DAL;
using SCPSInventory.Models;
using System;
using System.Data.Entity;

namespace SCPSInventory.Controllers
{
    public class AssetsController : Controller
    {
        private SCPSInventoryContext db = new SCPSInventoryContext();

        // GET: Assets/CostCenterList/0021
        public ActionResult CostCenterList(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            CostCenter costCenter = db.CostCenters.Find(id);
            if (costCenter == null)
            {
                return HttpNotFound();
            }
            costCenter.AssetList = db.Assets.Where(asset => asset.ccId == id).ToList();
            return View(costCenter);
        }

        // GET: Assets/InventoryList/5
        public ActionResult InventoryList(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = db.Inventories.Find(id);
            if (inventory == null)
            {
                return HttpNotFound();
            }
            inventory.AssetList = db.Assets.Where(asset => asset.ccId == inventory.ccId).ToList();
            //inventory.AssetList = db.Assets.Where(asset => asset.ccId == inventory.ccId && asset.InventoryDate < inventory.InventoryStartDate).ToList();
            inventory.numAssetsToInventory = inventory.AssetList.Count();
            inventory.numAssetsInventoried = inventory.AssetList.Count(asset => asset.InventoryDate >= inventory.InventoryStartDate);
            inventory.AssetList = db.Assets.Where(asset => asset.ccId == inventory.ccId && asset.InventoryDate < inventory.InventoryStartDate).ToList();
            return View(inventory);
        }

        // GET: Assets/Inventory/5
        public ActionResult Inventory(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = db.Inventories.Find(id);
            if (inventory == null)
            {
                return HttpNotFound();
            }
            //Hack: using Serial Number (otherwise unused by View()) to pass InventoryID for link back  
            Asset asset = new Asset { SerialNumber = id.ToString(), ccId = inventory.ccId };
            return View(asset);
        }

        // POST: Inventories/Inventory/5
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Inventory([Bind(Include = "AssetId, ccId, Building, Room, SerialNumber")] Asset asset)
        {
            Asset inventoried = db.Assets.Find(asset.AssetId);
            if (inventoried != null)
            {
                inventoried.ccId = asset.ccId;
                inventoried.Room = asset.Room;
                inventoried.Building = asset.Building;
                inventoried.InventoryDate = DateTime.Now;

                db.Entry(inventoried).State = EntityState.Modified;
                db.SaveChanges();
            }
            //Inventory Loop until user goes back to View Inventory
            return RedirectToAction("Inventory", "Assets", new { id = asset.SerialNumber });
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
